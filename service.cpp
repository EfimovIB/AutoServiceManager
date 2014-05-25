#include <QUuid>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QList>
#include <QString>
#include "service.h"
#include "person.h"
#include "asmapi.h"

namespace asmt
{
static const QString DateFormat("dd.MM.yyyy");

Service_old::Service_old(const Person_old* _client)
  : m_id(QUuid::createUuid().toString())
  , m_client(_client)
  , m_master(NULL)
  , m_aggregate(NULL)
  , m_price(0)
  , m_boxNumber(-1)
{
    addInDatabase();
}

Service_old::~Service_old()
{
    delete m_aggregate;
}

Service_old::Service_old()
    : m_master(NULL),
      m_aggregate(NULL)
{}

const QString& Service_old::id() const
{
    return m_id;
}

const QString& Service_old::masterComments() const
{
    return m_masterComments;
}

const QString& Service_old::clientComments() const
{
    return m_clientComments;
}

void Service_old::setClientComments(const QString& _comment)
{
    m_clientComments = _comment;
    updateClientCommentsInDatabase();
}

const Person_old* Service_old::client() const
{
    return m_client;
}

const Person_old* Service_old::master() const
{
    return m_master;
}

void Service_old::setMaster(const Person_old* _master)
{
    m_master = _master;
    updateMasterInDatabase();
}

const QDate& Service_old::startDate() const
{
    return m_startDate;
}

void Service_old::setStartDate(const QDate& _date)
{
    m_startDate = _date;
    updateStartDateInDatabase();
}

QString Service_old::startDateText() const
{
    if (m_startDate.isValid())
        return m_startDate.toString(DateFormat);

    return QString();
}

const QDate& Service_old::endDate() const
{
    return m_endDate;
}

QString Service_old::endDateText() const
{
    if (m_endDate.isValid())
        return m_endDate.toString(DateFormat);

    return QString();
}

QList<Service_old> Service_old::listByTextQueryCondition(const QString& _condition)
{
    QString text = "select id, clientId, masterId, aggregateId, boxNumber, changed, clientComments, masterComments, startDate, endDate, price from " + ServiceTableName + " where " + _condition;
    QSqlQuery query(text);
    QList<Service_old> list;

    if (query.isActive() == false)
    {
        qDebug() << "Database" << ServiceTableName << "query" << text << endl << query.lastError().databaseText();
        return list;
    }

    for (;query.next();)
    {
        Service_old s;
        s.m_id = query.value(0).toString();
        s.m_client = Person_old::person(query.value(1).toString());
        s.m_master = Person_old::person(query.value(2).toString());
        s.m_aggregate = Aggregate_old::aggregate(query.value(3).toInt());
        s.m_boxNumber = query.value(4).toInt();
        s.m_changed = query.value(5).toString();
        s.m_clientComments = query.value(6).toString();
        s.m_masterComments = query.value(7).toString();
        s.m_startDate = QDate::fromString(query.value(8).toString(), DateFormat);
        s.m_endDate = QDate::fromString(query.value(9).toString(), DateFormat);
        s.m_price = query.value(10).toFloat();
        list << s;
    }

    return list;
}

QList<Service_old> Service_old::services(const Person_old* _client)
{
    QString condition = "client_id = '" + _client->id() + "'";

    return listByTextQueryCondition(condition);
}

Aggregate_old *Service_old::aggregate() const
{
    return m_aggregate;
}

void Service_old::setAggregate(Aggregate_old *_aggregate)
{
    delete m_aggregate;
    m_aggregate = _aggregate;
    updateAggregateInDatabase();
}

int Service_old::boxNumber() const
{
    return m_boxNumber;
}

void Service_old::setBoxNumber(int _boxNumber)
{
    m_boxNumber = _boxNumber;
    updateBoxNumberInDatabase();
}

QList<Service_old> Service_old::servicesInProgress()
{
    QString condition = "endDate = ''";

    return listByTextQueryCondition(condition);
}

QList<Service_old> Service_old::servicesByStartDate(const QDate& _date)
{
    QString condition = "startDate = '" + _date.toString(DateFormat) + "'";

    return listByTextQueryCondition(condition);
}

QList<Service_old> Service_old::servicesByEndDate(const QDate& _date)
{
    QString condition = "endDate = '" + _date.toString(DateFormat) + "'";

    return listByTextQueryCondition(condition);
}

void Service_old::addInDatabase()
{
    QString clientId = m_client ? m_client->id() : QString();
    QString masterId = m_master ? m_master->id() : QString();
    QString priceSt = QString::number(m_price);
    QString aggregate = m_aggregate ? QString::number(m_aggregate->id()) : "-1";
    QString box = QString::number(m_boxNumber);

    QString text = "insert into " + ServiceTableName + "   values("
            "'" + m_id +             "', "
            "'" + clientId +         "', "
            "'" + masterId +         "', "
            ""  + aggregate+         ", "
            ""  + box        +       ", "
            "'" + m_clientComments + "', "
            "'" + m_masterComments + "', "
            "'" + m_changed +        "', "
            "'" + startDateText() +      "', "
            "'" + endDateText() +        "', "
            " " + priceSt +          ")";

    QSqlQuery query(text);

    if (query.isActive() == false)
        qDebug() << "Client addInDatabase query" << text << endl << query.lastError().databaseText();
}

void Service_old::updateClientCommentsInDatabase()
{
    QString text = "update " + ServiceTableName + "   set clientComments = '" + m_clientComments + "' where id = '" + m_id +"'";
    QSqlQuery query(text);

    if (query.isActive() == false)
        qDebug() << "Service setClientComments query" << text << endl << query.lastError().databaseText();
}

void Service_old::updateStartDateInDatabase()
{
    QString text = "update " + ServiceTableName + "   set startDate = '" + startDateText() + "' where id = '" + m_id +"'";
    QSqlQuery query(text);

    if (query.isActive() == false)
        qDebug() << "Service setStartDate query" << text << endl << query.lastError().databaseText();
}

void Service_old::updateMasterInDatabase()
{
    QString masterId;
    if (m_master)
        masterId = m_master->id();

    QString text = "update " + ServiceTableName + "   set masterId = '" + masterId + "' where id = '" + m_id +"'";
    QSqlQuery query(text);

    if (query.isActive() == false)
        qDebug() << "Service setMaster query" << text << endl << query.lastError().databaseText();
}

void Service_old::updateAggregateInDatabase()
{
    int aggregateId = m_aggregate ? m_aggregate->id() : -1;

    QString text = "update " + ServiceTableName + "   set aggregateId = " + QString::number(aggregateId) + " where id = '" + m_id +"'";
    QSqlQuery query(text);

    if (query.isActive() == false)
        qDebug() << "Service setAggregate query" << text << endl << query.lastError().databaseText();
}

void Service_old::updateBoxNumberInDatabase()
{
    QString text = "update " + ServiceTableName + "   set boxNumber = " + QString::number(m_boxNumber) + " where id = '" + m_id +"'";
    QSqlQuery query(text);

    if (query.isActive() == false)
        qDebug() << "Service setBoxNumber query" << text << endl << query.lastError().databaseText();
}

}
