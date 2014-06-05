#include <QSqlDatabase>
#include <QDebug>

#include "contentwidgetservicecreator.h"
#include "ui_contentwidgetservicecreator.h"
#include "datastructs.h"

namespace asmt
{

ContentWidgetServiceCreator::ContentWidgetServiceCreator(MainWidget* _mainWidget)
  : ContentWidget(_mainWidget)
  , m_ui(new Ui::ContentWidgetServiceCreator)
{
  m_ui->setupUi(this);

  m_ui->date->setDate(QDate::currentDate());
}

ContentWidgetServiceCreator::ContentWidgetServiceCreator(ContentWidget* _contentWidget)
  : ContentWidget(_contentWidget)
  , m_ui(new Ui::ContentWidgetServiceCreator)
{
  m_ui->setupUi(this);

  m_ui->date->setDate(QDate::currentDate());

  // -------------------------

  m_ui->name->setText(tr("К_И_1"));
  m_ui->surname->setText(tr("К_Ф_1"));
  m_ui->patronymic->setText(tr("К_О_1"));
  m_ui->telephone->setText(tr("К_T_1"));

  m_ui->agregateName->setText(tr("Стартер"));
  m_ui->agregateType->setText(tr("Механический"));
  m_ui->agregateNumber->setText("123456789");
  m_ui->car->setText(tr("Машина"));
  m_ui->boxNumber->setText("5");
  m_ui->comments->setPlainText(tr("Не работает"));
}

ContentWidgetServiceCreator::~ContentWidgetServiceCreator()
{
    delete m_ui;
}

void ContentWidgetServiceCreator::topButtonclicked()
{
    // if () // todo add checking

    QSqlDatabase::database().transaction();

    Person p; // todo search Person by phone number

    p.surname = m_ui->surname->text();
    p.name = m_ui->name->text();
    p.patronymic = m_ui->patronymic->text();
    p.phone += m_ui->telephone->text();

    if (p.insertInDatabase() == false)
    {
        QSqlDatabase::database().rollback();

        return;
    }

    Aggregate a;

    a.name = m_ui->agregateName->text();
    a.number = m_ui->agregateNumber->text();
    a.type = AggregateType(m_ui->agregateName->text());
    a.car = Car(m_ui->car->text());

    if (a.insertInDatabase() == false)
    {
        QSqlDatabase::database().rollback();

        return;
    }

    Service s;
    s.aggregate = a;
    s.person = p;
    s.startDate = m_ui->date->date();
    s.personComments = m_ui->comments->toPlainText();

    if (s.insertInDatabase() == false)
    {
        QSqlDatabase::database().rollback();

        return;
    }

    QSqlDatabase::database().commit();

    emit created();

    switchOnPrev();

    clearForm();
}

void ContentWidgetServiceCreator::clearForm()
{
    m_ui->name->clear();
    m_ui->surname->clear();
    m_ui->patronymic->clear();
    m_ui->telephone->clear();
    m_ui->agregateName->clear();
    m_ui->agregateNumber->clear();
    m_ui->agregateType->clear();
    m_ui->boxNumber->clear();
    m_ui->car->clear();
    m_ui->comments->clear();
    m_ui->date->setDate(QDate::currentDate());
}

}
