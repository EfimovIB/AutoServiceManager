#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

#include "goods.h"
#include "asmapi.h"

namespace asmt
{
Goods::Goods(const QString& _barcode, const QString& _name, int _count)
	: QObject(),
	m_barcode(_barcode),
	m_name(_name),
	m_count(_count)
{
	initInDatabase();
}

Goods::Goods(const QString& _barcode, int _count)
	: QObject(),
	m_barcode(_barcode),
	m_count(_count)
{
	initInDatabase();
}

Goods::Goods()
{
}

const QString& Goods::barcode() const
{
	return m_barcode;
}

const QString& Goods::name() const
{
	return m_name;
}

int Goods::count() const
{
	return m_count;
}

QList<Goods*> Goods::goods()
{
	QString text = "select barcode, name, count from " + WarehouseTableName;
	QSqlQuery query(text);
	QList<Goods*> list;
	if (query.isActive() == false)
	{
		qDebug() << "Database goods query" << text << endl << query.lastError().databaseText ();
		return list;
	}

	for (;query.next();)
	{
		QString barcode = query.value(0).toString();
		QString name = query.value(1).toString();
		int count = query.value(2).toInt();
		Goods* g = new Goods;
		g->m_barcode = barcode;
		g->m_name = name;
		g->m_count = count;
		list << g;
	}

	return list;
}

void Goods::setName(const QString& _name)
{
	m_name = _name;
	QString text = "update " + WarehouseTableName + "   set name = '" + _name + "' where barcode = '" + m_barcode +"'";
	QSqlQuery query(text);

	if (query.isActive() == false)
		qDebug() << "Goods setName query" << text << endl << query.lastError().databaseText ();
}

void Goods::refCount(int _ref)
{
	m_count += _ref;
	QString text = "update " + WarehouseTableName + "   set count = " + m_count + " where barcode = '" + m_barcode +"'";
	QSqlQuery query(text);

	if (query.isActive() == false)
		qDebug() << "Goods refCount query" << text << endl << query.lastError().databaseText ();
}

void Goods::initInDatabase()
{
	QString text = "insert into " + WarehouseTableName + "   values ('" + m_barcode + "', '" + m_name + "', " + QString::number(m_count) + ")";
	QSqlQuery query(text);

	if (query.isActive() == false)
		qDebug() << "Goods initInDatabase query" << text << endl << query.lastError().databaseText ();
}

}