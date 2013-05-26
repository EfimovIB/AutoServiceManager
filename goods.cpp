#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

#include "goods.h"
#include "manufacturer.h"
#include "asmapi.h"

namespace asmt
{
Goods::Goods(const QString& _barcode, const QString& _name, int _count)
	: QObject(),
	m_barcode(_barcode),
	m_name(_name),
	m_manufacturer(NULL),
	m_count(_count)
{
	addInDatabase();
}

Goods::Goods(const QString& _barcode, int _count)
	: QObject(),
	m_barcode(_barcode),
	m_manufacturer(NULL),
	m_count(_count)
{
	addInDatabase();
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

const Manufacturer const* Goods::manufacturer() const
{
	return m_manufacturer;
}

QString Goods::manufacturerName() const
{
	if (m_manufacturer)
		return m_manufacturer->name();
	
	return QString();
}

void Goods::setManufacturer(int _id)
{
	if (const Manufacturer const* m = Manufacturer::manufacturer(_id))
		m_manufacturer = m;
	else
		m_manufacturer = NULL;

	updateManufacturerInDatabase();
}

QList<Goods*> Goods::goods()
{
	QString text = "select barcode, name, manufacturer, count from " + WarehouseTableName;
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
		int manuf = query.value(2).toInt();
		int count = query.value(3).toInt();
		Goods* g = new Goods;
		g->m_barcode = barcode;
		g->m_name = name;
		g->m_count = count;
		g->m_manufacturer = Manufacturer::manufacturer(manuf);
		list << g;
	}

	return list;
}

void Goods::setName(const QString& _name)
{
	m_name = _name;
	updateNameInDatabase();
}

void Goods::refCount(int _ref)
{
	m_count += _ref;
	QString text = "update " + WarehouseTableName + " set count = " + QString::number(m_count) + " where barcode = '" + m_barcode +"'";
	QSqlQuery query(text);

	if (query.isActive() == false)
		qDebug() << "Goods refCount query" << text << endl << query.lastError().databaseText ();
}

void Goods::addInDatabase()
{
	QString manufact = manufacturerValueToDatabase();
	QString text = "insert into " + WarehouseTableName + "   values('" + m_barcode + "', '" + m_name + "', " + manufact + ", " + QString::number(m_count) + ")";

	QSqlQuery query(text);

	if (query.isActive() == false)
		qDebug() << "Goods addInDatabase query" << text << endl << query.lastError().databaseText();
}

void Goods::updateNameInDatabase()
{
	QString text = "update " + WarehouseTableName + "   set name = '" + m_name + "' where barcode = '" + m_barcode +"'";
	QSqlQuery query(text);

	if (query.isActive() == false)
		qDebug() << "Goods setName query" << text << endl << query.lastError().databaseText ();
}

void Goods::updateManufacturerInDatabase()
{
	QString manufact = manufacturerValueToDatabase();
	QString text = "update " + WarehouseTableName + "   set manufacturer = " + manufact + " where barcode = '" + m_barcode +"'";
	QSqlQuery query(text);

	if (query.isActive() == false)
		qDebug() << "Goods setManufacturer query" << text << endl << query.lastError().databaseText ();
}

QString Goods::manufacturerValueToDatabase() const
{
	return m_manufacturer ? QString::number(m_manufacturer->id()) : "-1";
}

}