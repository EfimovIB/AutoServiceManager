#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>

#include "contentwidgetmasterscreator.h"
#include "ui_ContentWidgetMastersCreator.h"
#include "asmapi.h"
#include "datastructs.h"

namespace asmt
{

ContentWidgetMastersCreator::ContentWidgetMastersCreator(MainWidget* _mainWidget, bool masterCreator)
  : ContentWidget(_mainWidget)
  , m_masterCreator(masterCreator)
{
    init();
    // todo: rename class
}

ContentWidgetMastersCreator::ContentWidgetMastersCreator(ContentWidget*_prev, bool masterCreator)
  : ContentWidget(_prev)
  , m_masterCreator(masterCreator)
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

    if (m_masterCreator)
    {
        m_ui->name->setText(tr("МИ1"));
        m_ui->surname->setText(tr("МФ1"));
        m_ui->patronymic->setText(tr("МО1"));
        m_ui->telephone->setText(tr("МТ1"));
    }
    else
    {
        m_ui->name->setText(tr("КИ1"));
        m_ui->surname->setText(tr("КФ1"));
        m_ui->patronymic->setText(tr("КО1"));
        m_ui->telephone->setText(tr("КТ1"));
    }
}

bool ContentWidgetMastersCreator::insertDataInDatabase()
{
    QSqlDatabase::database().transaction();

    Person p;
    p.name = m_ui->name->text();
    p.surname = m_ui->surname->text();
    p.patronymic = m_ui->patronymic->text();
    p.phone << m_ui->telephone->text();

    if (m_masterCreator)
    {
        Master m;
        m.person = p;
        m.date = QDate::currentDate();

        if (!m.insertInDatabase())
        {
            QSqlDatabase::database().rollback();

            return false;
        }
    }
    else
    {
        if (!p.insertInDatabase())
        {
            QSqlDatabase::database().rollback();

            return false;
        }
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
