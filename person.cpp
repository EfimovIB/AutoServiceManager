#include <QUuid>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

#include "person.h"
#include "asmapi.h"

namespace asmt
{
static QList<Person*> ListClients;
static bool WasLoaded = false;

Person::Person()
{}

Person::Person(const QString& _name, Type _type)
  : m_type(_type)
  , m_name(_name)
  , m_id(QUuid::createUuid().toString())
{
    addInDatabase();
    ListClients << this;
}

Person::Type Person::type() const
{
    return m_type;
}

const QString& Person::name() const
{
    return m_name;
}

void Person::setName(const QString& _name)
{
    m_name = _name;
    updateNameInDatabase();
}

const QString& Person::surname() const
{
    return m_surname;
}

void Person::setSurname(const QString& _surname)
{
    m_surname = _surname;
    updateSurnameInDatabase();
}

const QString& Person::patronymic() const
{
    return m_patronymic;
}

void Person::setPatronymic(const QString& _patronymic)
{
    m_patronymic = _patronymic;
    updatePatronymicInDatabase();
}

QString Person::fullName() const
{
    return m_surname + " " + m_name + " " + m_patronymic;
}

const QStringList& Person::phones() const
{
    return m_phones;
}

void Person::setPhones(const QStringList& _phones)
{
    m_phones = _phones;
    updatePhonesInDatabase();
}

const QString& Person::id() const
{
    return m_id;
}

QList<Person*> Person::persons(Type _type)
{
    checkListClients();

    QList<Person*> l;

    foreach(Person* p, ListClients)
        if (p->type() == _type)
            l << p;

    return l;
}

Person* Person::person(const QString& _id)
{
    checkListClients();

    foreach(Person* p, ListClients)
        if (p->m_id == _id)
            return p;

    return NULL;
}

void Person::checkListClients()
{
    if (WasLoaded)
        return;

    dowloadClients();
    WasLoaded = true;
}

void Person::dowloadClients()
{
    QString text = "select id, name, surname, patronymic, phones, type from " + PersonTableName;
    QSqlQuery query(text);
    if (query.isActive() == false)
        qDebug() << "Database goods query" << text << endl << query.lastError().databaseText ();

    for (;query.next();)
    {
        Person* g = new Person;
        g->m_id = query.value(0).toString();
        g->m_name = query.value(1).toString();
        g->m_surname = query.value(2).toString();
        g->m_patronymic = query.value(3).toString();
        g->m_phones = query.value(4).toString().split(" ");
        g->m_type = Person::Type(query.value(5).toInt());

        ListClients << g;
    }
}

void Person::addInDatabase()
{
    QString text = "insert into " + PersonTableName + "   values('" + m_id + "', '" + m_name + "', '" + m_surname + "', '" + m_patronymic + "', '" + m_phones.join(" ") + "', " + QString::number(m_type)+ ")";

    QSqlQuery query(text);

    if (query.isActive() == false)
        qDebug() << "Client addInDatabase query" << text << endl << query.lastError().databaseText();
}

void Person::updateNameInDatabase()
{
    QString text = "update " + PersonTableName + "   set name = '" + m_name + "' where id = '" + m_id +"'";
    QSqlQuery query(text);

    if (query.isActive() == false)
        qDebug() << "Client setName query" << text << endl << query.lastError().databaseText ();
}

void Person::updateSurnameInDatabase()
{
    QString text = "update " + PersonTableName + "   set surname = '" + m_surname + "' where id = '" + m_id +"'";
    QSqlQuery query(text);

    if (query.isActive() == false)
        qDebug() << "Client setSurname query" << text << endl << query.lastError().databaseText ();
}

void Person::updatePatronymicInDatabase()
{
    QString text = "update " + PersonTableName + "   set patronymic = '" + m_patronymic + "' where id = '" + m_id +"'";
    QSqlQuery query(text);

    if (query.isActive() == false)
        qDebug() << "Client setPatronymic query" << text << endl << query.lastError().databaseText ();
}

void Person::updatePhonesInDatabase()
{
    QString text = "update " + PersonTableName + "   set phones = '" + m_phones.join(" ") + "' where id = '" + m_id +"'";
    QSqlQuery query(text);

    if (query.isActive() == false)
        qDebug() << "Client setPhones query" << text << endl << query.lastError().databaseText ();
}


}
