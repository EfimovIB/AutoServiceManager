#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "databasemanager.h"

namespace asmt
{
const QString WarehouseTableName("warehouse");

DatabaseManager::DatabaseManager() {}

void DatabaseManager::connect()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
	db.setHostName("127.0.0.1");
	db.setDatabaseName("asm");// CREATE DATABASE
	db.setUserName("postgres");
	db.setPassword("12345678");

	m_connectError.clear();
	if (db.open() == false)
		m_connectError = db.lastError().databaseText ();
}

bool DatabaseManager::open() const
{
	return m_connectError.isEmpty();
}

QString DatabaseManager::error() const
{
	return m_connectError;
}

void DatabaseManager::initTables() const
{
	QString text = "create table " + WarehouseTableName + " ("
						"barcode    varchar(80) not null,"
						"name varchar(100),"
						"count int"
						");";

	QSqlQuery query(text);

	if (query.isActive() == false)
		qDebug() << "Database initTables query" << text << endl  << query.lastError().databaseText ();
}

void DatabaseManager::dropTables() const
{
	dropTable(WarehouseTableName);
}

void DatabaseManager::dropTable(const QString& _name) const
{
	QString text ="drop table " + _name;
	QSqlQuery query(text);

	if (query.isActive() == false)
		qDebug() << "Database dropTable query" << text << endl << query.lastError().databaseText ();
}

void DatabaseManager::addGoods(const QString& _barcode, const QString& _name)
{
	QString text = "insert into " + WarehouseTableName + "   values ('" + _barcode + "', '" + _name + "', 0)";
	QSqlQuery query(text);

	if (query.isActive() == false)
		qDebug() << "Database addGoods query" << text << endl << query.lastError().databaseText ();
}

void DatabaseManager::addGoods(const QString& _barcode, int _count)
{
	QString text = "update " + WarehouseTableName + "   set count = count + " + QString::number(_count)+ " where barcode = '" + _barcode +"'";
	QSqlQuery query(text);

	if (query.isActive() == false)
		qDebug() << "Database addGoods query" << text << endl << query.lastError().databaseText ();
}

void DatabaseManager::refGoods(const QString& _barcode)
{
	QString text = "update " + WarehouseTableName + "   set count = count + 1 where barcode = '" + _barcode +"'";
	QSqlQuery query(text);

	if (query.isActive() == false)
		qDebug() << "Database refGoods query" << text << endl << query.lastError().databaseText ();
}

void DatabaseManager::derefGoods(const QString& _barcode)
{
	QString text = "update " + WarehouseTableName + "   set count = count - 1 where barcode = '" + _barcode +"'";
	QSqlQuery query(text);

	if (query.isActive() == false)
		qDebug() << "Database derefGoods query" << text << endl << query.lastError().databaseText ();
}

bool DatabaseManager::exist(const QString& _barcode) const
{
	QString text = "select * from " + WarehouseTableName + " where barcode = '" + _barcode +"'";
	QSqlQuery query(text);

	if (query.isActive() == false)
		qDebug() << "Database exist query" << text << endl << query.lastError().databaseText ();

	return query.first();
}

QList<Goods> DatabaseManager::goods() const
{
	QString text = "select barcode, name, count from " + WarehouseTableName;
	QSqlQuery query(text);

	QList<Goods> list;

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
		list << Goods(barcode, name, count);
	}

	return list;
}

}