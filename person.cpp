#include <QUuid>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

#include "person.h"
#include "asmapi.h"

namespace asmt
{
static QList<Person_old*> ListClients;
static bool WasLoaded = false;

Person_old::Person_old()
{}

Person_old::Person_old(const QString& _name, Type _type)
  : m_type(_type)
  , m_name(_name)
  , m_id(QUuid::createUuid().toString())
{
    addInDatabase();
    ListClients << this;
}

Person_old::Type Person_old::type() const
{
    return m_type;
}

const QString& Person_old::name() const
{
    return m_name;
}

void Person_old::setName(const QString& _name)
{
    m_name = _name;
    updateNameInDatabase();
}

const QString& Person_old::surname() const
{
    return m_surname;
}

void Person_old::setSurname(const QString& _surname)
{
    m_surname = _surname;
    updateSurnameInDatabase();
}

const QString& Person_old::patronymic() const
{
    return m_patronymic;
}

void Person_old::setPatronymic(const QString& _patronymic)
{
    m_patronymic = _patronymic;
    updatePatronymicInDatabase();
}

QString Person_old::fullName() const
{
    return m_surname + " " + m_name + " " + m_patronymic;
}

const QStringList& Person_old::phones() const
{
    return m_phones;
}

void Person_old::setPhones(const QStringList& _phones)
{
    m_phones = _phones;
    updatePhonesInDatabase();
}

const QString& Person_old::id() const
{
    return m_id;
}

QList<Person_old*> Person_old::persons(Type _type)
{
    checkListClients();

    QList<Person_old*> l;

    foreach(Person_old* p, ListClients)
        if (p->type() == _type)
            l << p;

    return l;
}

Person_old* Person_old::person(const QString& _id)
{
    checkListClients();

    foreach(Person_old* p, ListClients)
        if (p->m_id == _id)
            return p;

    return NULL;
}

void Person_old::checkListClients()
{
    if (WasLoaded)
        return;

    dowloadClients();
    WasLoaded = true;
}

void Person_old::dowloadClients()
{
    QString text = "select id, name, surname, patronymic, phones, type from " + PersonTableName;
    QSqlQuery query(text);
    if (query.isActive() == false)
        qDebug() << "Database goods query" << text << endl << query.lastError().databaseText ();

    for (;query.next();)
    {
        Person_old* g = new Person_old;
        g->m_id = query.value(0).toString();
        g->m_name = query.value(1).toString();
        g->m_surname = query.value(2).toString();
        g->m_patronymic = query.value(3).toString();
        g->m_phones = query.value(4).toString().split(" ");
        g->m_type = Person_old::Type(query.value(5).toInt());

        ListClients << g;
    }
}

void Person_old::addInDatabase()
{
    QString text = "insert into " + PersonTableName + "   values('" + m_id + "', '" + m_name + "', '" + m_surname + "', '" + m_patronymic + "', '" + m_phones.join(" ") + "', " + QString::number(m_type)+ ")";

    QSqlQuery query(text);

    if (query.isActive() == false)
        qDebug() << "Client addInDatabase query" << text << endl << query.lastError().databaseText();
}

void Person_old::updateNameInDatabase()
{
    QString text = "update " + PersonTableName + "   set name = '" + m_name + "' where id = '" + m_id +"'";
    QSqlQuery query(text);

    if (query.isActive() == false)
        qDebug() << "Client setName query" << text << endl << query.lastError().databaseText ();
}

void Person_old::updateSurnameInDatabase()
{
    QString text = "update " + PersonTableName + "   set surname = '" + m_surname + "' where id = '" + m_id +"'";
    QSqlQuery query(text);

    if (query.isActive() == false)
        qDebug() << "Client setSurname query" << text << endl << query.lastError().databaseText ();
}

void Person_old::updatePatronymicInDatabase()
{
    QString text = "update " + PersonTableName + "   set patronymic = '" + m_patronymic + "' where id = '" + m_id +"'";
    QSqlQuery query(text);

    if (query.isActive() == false)
        qDebug() << "Client setPatronymic query" << text << endl << query.lastError().databaseText ();
}

void Person_old::updatePhonesInDatabase()
{
    QString text = "update " + PersonTableName + "   set phones = '" + m_phones.join(" ") + "' where id = '" + m_id +"'";
    QSqlQuery query(text);

    if (query.isActive() == false)
        qDebug() << "Client setPhones query" << text << endl << query.lastError().databaseText ();
}


}
