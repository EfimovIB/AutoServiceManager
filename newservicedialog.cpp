#include <QDebug>

#include "newservicedialog.h"
#include "ui_NewServiceDialog.h"

#include "person.h"
#include "service.h"
#include "aggregate.h"

namespace asmt
{
NewServiceDialog::NewServiceDialog(QWidget* _parent)
  : QDialog(_parent)
  , m_ui(new Ui::NewServiceDialog)
{
    m_ui->setupUi(this);
    m_ui->date->setDate(QDate::currentDate());
    m_masters = Person::persons(Person::Master);
    m_ui->masters->addItem("Мастер");
    foreach(Person* p, m_masters)
        m_ui->masters->addItem(p->fullName());
}

NewServiceDialog::~NewServiceDialog()
{
    delete m_ui;
}

const QDate& NewServiceDialog::date() const
{
    return m_ui->date->date();
}

Person* NewServiceDialog::master() const
{
    int num = m_ui->masters->currentIndex();

    if (num < 1)
        return NULL;

    return m_masters[num - 1];
}

Aggregate *NewServiceDialog::createAggregate() const
{
    QString name = m_ui->name->text();
    QString type = m_ui->type->text();
    QString car = m_ui->car->text();
    QString number = m_ui->number->text();

    if (name.isEmpty() && type.isEmpty() && car.isEmpty() && number.isEmpty())
        return NULL;

    return new Aggregate(name, type, car, number);
}

QString NewServiceDialog::comment() const
{
    return m_ui->comments->toPlainText();
}

int NewServiceDialog::box() const
{
    return m_ui->box->text().toInt();
}

Service* NewServiceDialog::createNewService(Person* _client, QWidget* _parent)
{
    Service* s(NULL);
    NewServiceDialog d(_parent);

    if (d.exec() == QDialog::Accepted)
    {
        s = new Service(_client);
        s->setStartDate(d.date());
        s->setClientComments(d.comment());
        s->setMaster(d.master());
        s->setAggregate(d.createAggregate());
        s->setBoxNumber(d.box());
    }

    return s;
}

}
