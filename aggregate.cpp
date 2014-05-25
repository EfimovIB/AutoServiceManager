#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

#include "aggregate.h"
#include "asmapi.h"

namespace asmt
{

Aggregate_old::Aggregate_old()
  : m_id(-1)
{}

Aggregate_old::Aggregate_old(const QString& _name, const QString& _type, const QString& _car, const QString& _number)
  : m_id(-1)
  , m_name(_name)
  , m_type(_type)
  , m_car(_car)
  , m_number(_number)
{
    addInDatabase();
    m_id = maxValue();
}

int Aggregate_old::id() const
{
    return m_id;
}

void Aggregate_old::setId(int _id)
{
    m_id = _id;
}

QString Aggregate_old::number() const
{
    return m_number;
}

void Aggregate_old::setNumber(const QString& _number)
{
    m_number = _number;
}

QString Aggregate_old::car() const
{
    return m_car;
}

void Aggregate_old::setCar(const QString& _car)
{
    m_car = _car;
}

QString Aggregate_old::type() const
{
    return m_type;
}

void Aggregate_old::setType(const QString& _agregatType)
{
    m_type = _agregatType;
}

QString Aggregate_old::name() const
{
    return m_name;
}

void Aggregate_old::setName(const QString& _agregatName)
{
    m_name = _agregatName;
}

Aggregate_old* Aggregate_old::aggregate(int _id)
{
    QString text = "select name, type, car, number from " + AggregateTableName + " where id = " + QString::number(_id);
    QSqlQuery query(text);

    if (query.isActive() == false || false == query.next())
    {
        qDebug() << "Database" << AggregateTableName << "query" << text << endl << query.lastError().databaseText();
        return NULL;
    }

    Aggregate_old* a = new Aggregate_old;
    a->m_id = _id;
    a->m_name = query.value(0).toString();
    a->m_type = query.value(1).toString();
    a->m_car = query.value(2).toString();
    a->m_number = query.value(3).toString();
    return a;
}

void Aggregate_old::addInDatabase()
{
    QString id = QString::number(maxValue() + 1);
    QString text = "insert into " + AggregateTableName + "   values("
            ""  + id +          ", "
            "'" + m_name +      "', "
            "'" + m_type +      "', "
            "'" + m_car  +      "', "
            "'" + m_number +    "')";

    QSqlQuery query(text);

    if (query.isActive() == false)
        qDebug() << "Aggregate addInDatabase query" << text << endl << query.lastError().databaseText();
}

int Aggregate_old::maxValue() const
{
    QString text = "SELECT MAX(id) AS value FROM " + AggregateTableName;

     QSqlQuery query(text);
     if (false == query.isActive() || false == query.next())
     {
         qDebug() << "Database" << AggregateTableName << "query" << text << endl << query.lastError().databaseText();
         return -1;
     }

     return query.value(3).toInt();
}

}
