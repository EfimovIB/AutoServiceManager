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
}

ContentWidgetServiceCreator::ContentWidgetServiceCreator(ContentWidget* _contentWidget)
  : ContentWidget(_contentWidget)
  , m_ui(new Ui::ContentWidgetServiceCreator)
{
  m_ui->setupUi(this);
}

ContentWidgetServiceCreator::~ContentWidgetServiceCreator()
{
    delete m_ui;
}

void ContentWidgetServiceCreator::topButtonclicked()
{
    // if () // todo add checking

    // todo firstly Service Creator

    QSharedPointer<Person> p(new Person); // todo search Person by phone number

    p->surname = m_ui->surname->text();
    p->name = m_ui->name->text();
    p->patronymic = m_ui->patronymic->text();
    p->phone += m_ui->telephone->text();

    QSharedPointer<Agregate> a(new Agregate);

    a->name = m_ui->agregateName->text();
    a->number = m_ui->agregateNumber->text().toUInt();
    a->type = AgregateType(m_ui->agregateName->text());

    emit created();
    // todo add clearing and switch
}

}
