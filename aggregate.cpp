#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

#include "aggregate.h"
#include "asmapi.h"

namespace asmt
{

Aggregate::Aggregate()
  : m_id(-1)
{}

Aggregate::Aggregate(const QString& _name, const QString& _type, const QString& _car, const QString& _number)
  : m_id(-1)
  , m_name(_name)
  , m_type(_type)
  , m_car(_car)
  , m_number(_number)
{
    addInDatabase();
    m_id = maxValue();
}

int Aggregate::id() const
{
    return m_id;
}

void Aggregate::setId(int _id)
{
    m_id = _id;
}

QString Aggregate::number() const
{
    return m_number;
}

void Aggregate::setNumber(const QString& _number)
{
    m_number = _number;
}

QString Aggregate::car() const
{
    return m_car;
}

void Aggregate::setCar(const QString& _car)
{
    m_car = _car;
}

QString Aggregate::type() const
{
    return m_type;
}

void Aggregate::setType(const QString& _agregatType)
{
    m_type = _agregatType;
}

QString Aggregate::name() const
{
    return m_name;
}

void Aggregate::setName(const QString& _agregatName)
{
    m_name = _agregatName;
}

Aggregate* Aggregate::aggregate(int _id)
{
    QString text = "select name, type, car, number from " + AggregateTableName + " where id = " + QString::number(_id);
    QSqlQuery query(text);

    if (query.isActive() == false || false == query.next())
    {
        qDebug() << "Database" << AggregateTableName << "query" << text << endl << query.lastError().databaseText();
        return NULL;
    }

    Aggregate* a = new Aggregate;
    a->m_id = _id;
    a->m_name = query.value(0).toString();
    a->m_type = query.value(1).toString();
    a->m_car = query.value(2).toString();
    a->m_number = query.value(3).toString();
    return a;
}

void Aggregate::addInDatabase()
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

int Aggregate::maxValue() const
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
