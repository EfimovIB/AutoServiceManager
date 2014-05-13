#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>

#include "contentwidgetmasterscreator.h"
#include "ui_ContentWidgetMastersCreator.h"
#include "asmapi.h"
namespace asmt
{

ContentWidgetMastersCreator::ContentWidgetMastersCreator(MainWidget* _mainWidget)
  : ContentWidget(_mainWidget)
{
    init();
}

ContentWidgetMastersCreator::ContentWidgetMastersCreator(ContentWidget*_prev)
    : ContentWidget(_prev)
{
    init();
}

ContentWidgetMastersCreator::~ContentWidgetMastersCreator()
{
    delete m_ui;
}

void ContentWidgetMastersCreator::topButtonclicked()
{
    if (dataEnough())
    {
        if (insertDataInDatabase())
        {
            clearForm();

            emit created();

            switchOnPrev();
        }
        else
        {
            m_ui->messageLabel->setText(tr("Ошибка отправки запроса"));
        }
    }
    else
    {
        m_ui->messageLabel->setText(tr("Не достаточно данных"));
    }
}

void ContentWidgetMastersCreator::bottomButtonclicked()
{
    clearForm();

    switchOnPrev();
}

void ContentWidgetMastersCreator::init()
{
    m_ui = new Ui::ContentWidgetMastersCreator;
    m_ui->setupUi(this);
    m_ui->name->setText(tr("МИ1"));
    m_ui->surname->setText(tr("МФ1"));
    m_ui->patronymic->setText(tr("МО1"));
    m_ui->telephone->setText(tr("МТ1"));
}

bool ContentWidgetMastersCreator::insertDataInDatabase()
{
    QSqlDatabase::database().transaction();

    QString text = "insert into " + PersonTableName + "(name, surname, patronymic) values("
                              "'" + m_ui->name->text() + "'"
                            ", '" + m_ui->surname->text() + "'"
                            ", '" + m_ui->patronymic->text() + "')";

    QSqlQuery query(text);

    if (query.isActive() == false)
    {
        qDebug() << "MastersCreator insertDataInDatabase query " << text << endl << query.lastError().databaseText();

        QSqlDatabase::database().rollback();

        return false;
    }

    text = "insert into " + PhoneTableName + " values("
                      "'" + m_ui->telephone->text() + "'"
                      ", (select max(id) from " + PersonTableName + "))";

    query.exec(text);

    if (query.isActive() == false)
    {
        qDebug() << "MastersCreator insertDataInDatabase query " << text << endl << query.lastError().databaseText();

        QSqlDatabase::database().rollback();

        return false;
    }

    text = "insert into " + MasterTableName + "(idPerson, idMasterState, startDate) values("
  "(select max(id) from " + PersonTableName + ")"
                     ", " + QString::number(Works) +
                    ", '" + QDate::currentDate().toString(DbDateFormat)+ "')";

    query.exec(text);

    if (query.isActive() == false)
    {
        qDebug() << "MastersCreator insertDataInDatabase query " << text << endl << query.lastError().databaseText();

        QSqlDatabase::database().rollback();

        return false;
    }

    QSqlDatabase::database().commit();

    return true;
}

bool ContentWidgetMastersCreator::dataEnough() const
{
    return m_ui->name->text().isEmpty() == false && m_ui->telephone->text().isEmpty()  == false;
}

void ContentWidgetMastersCreator::clearForm()
{
    m_ui->name->clear();
    m_ui->patronymic->clear();
    m_ui->surname->clear();
    m_ui->telephone->clear();
    m_ui->messageLabel->clear();
}

}
