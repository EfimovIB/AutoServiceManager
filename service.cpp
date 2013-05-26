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

	Service::Service(const Person const* _client)
		: m_id(QUuid::createUuid()),
		m_client(_client),
		m_master(NULL),
		m_price(0)
	{
		addInDatabase();
	}

	Service::Service()
	{}

	const QString& Service::id() const
	{
		return m_id;
	}

	const QString& Service::masterComments() const
	{
		return m_masterComments;
	}

	const QString& Service::clientComments() const
	{
		return m_clientComments;
	}

	void Service::setClientComments(const QString& _comment)
	{
		m_clientComments = _comment;
		updateClientCommentsInDatabase();
	}

	const Person const* Service::client() const
	{
		return m_client;
	}

	const Person const* Service::master() const
	{
		return m_master;
	}

	void Service::setMaster(const Person const* _master)
	{
		m_master = _master;
		updateMasterInDatabase();
	}

	const QDate& Service::startDate() const
	{
		return m_startDate;
	}

	void Service::setStartDate(const QDate& _date)
	{
		m_startDate = _date;
		updateStartDateInDatabase();
	}

	QString Service::startDateText() const
	{
		if (m_startDate.isValid())
			return m_startDate.toString(DateFormat);

		return QString();
	}

	const QDate& Service::endDate() const
	{
		return m_endDate;
	}

	QString Service::endDateText() const
	{
		if (m_endDate.isValid())
			return m_endDate.toString(DateFormat);

		return QString();
	}

	QList<Service> Service::listByTextQueryCondition(const QString& _condition)
	{
		QString text = "select id, clientId, masterId, changed, clientComments, masterComments, startDate, endDate, price from " + ServiceTableName + " where " + _condition;
		QSqlQuery query(text);
		QList<Service> list;

		if (query.isActive() == false)
		{
			qDebug() << "Database service query" << text << endl << query.lastError().databaseText();
			return list;
		}

		for (;query.next();)
		{
			Service s;
			s.m_id = query.value(0).toString();
			s.m_client = Person::person(query.value(1).toString());
			s.m_master = Person::person(query.value(2).toString());
			s.m_changed = query.value(3).toString();
			s.m_clientComments = query.value(4).toString();
			s.m_masterComments = query.value(5).toString();
			s.m_startDate = QDate::fromString(query.value(6).toString(), DateFormat);
			s.m_endDate = QDate::fromString(query.value(7).toString(), DateFormat);
			s.m_price = query.value(8).toFloat();
			list << s;
		}

		return list;
	}

	QList<Service> Service::services(const Person const* _client)
	{
		QString condition = "client_id = '" + _client->id() + "'";

		return listByTextQueryCondition(condition);
	}

	QList<Service> Service::servicesInProgress()
	{
		QString condition = "endDate = ''";

		return listByTextQueryCondition(condition);
	}

	QList<Service> Service::servicesByStartDate(const QDate& _date)
	{
		QString condition = "startDate = '" + _date.toString(DateFormat) + "'";

		return listByTextQueryCondition(condition);
	}

	QList<Service> Service::servicesByEndDate(const QDate& _date)
	{
		QString condition = "endDate = '" + _date.toString(DateFormat) + "'";

		return listByTextQueryCondition(condition);
	}

	void Service::addInDatabase()
	{
		QString clientId = m_client ? m_client->id() : QString();
		QString masterId = m_master ? m_master->id() : QString();
		QString priceSt = QString::number(m_price);

		QString text = "insert into " + ServiceTableName + "   values("
		"'" + m_id +             "', "
		"'" + clientId +         "', "
		"'" + masterId +         "', "
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

	void Service::updateClientCommentsInDatabase()
	{
		QString text = "update " + ServiceTableName + "   set clientComments = '" + m_clientComments + "' where id = '" + m_id +"'";
		QSqlQuery query(text);

		if (query.isActive() == false)
			qDebug() << "Service setClientComments query" << text << endl << query.lastError().databaseText();
	}

	void Service::updateStartDateInDatabase()
	{
		QString text = "update " + ServiceTableName + "   set startDate = '" + startDateText() + "' where id = '" + m_id +"'";
		QSqlQuery query(text);

		if (query.isActive() == false)
			qDebug() << "Service setStartDate query" << text << endl << query.lastError().databaseText();
	}

	void Service::updateMasterInDatabase()
	{
		QString masterId;
		if (m_master)
			masterId = m_master->id();

		QString text = "update " + ServiceTableName + "   set masterId = '" + masterId + "' where id = '" + m_id +"'";
		QSqlQuery query(text);

		if (query.isActive() == false)
			qDebug() << "Service setMaster query" << text << endl << query.lastError().databaseText();
	}

}