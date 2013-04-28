#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

#include "databasemanager.h"
#include "asmapi.h"

namespace asmt
{

void DatabaseManager::initTables()
{
	QString text = "create table " + WarehouseTableName + " ("
						"barcode    varchar(80) not null,"
						"name varchar(100),"
						"count int"
						");";
	execInitTable(text);
	
	text = "create table " + ManufacturerTableName + " ("
		"id   int not null,"
		"name varchar(100)"
		");";

	execInitTable(text);
}

void DatabaseManager::dropTables()
{
	dropTable(WarehouseTableName);
	dropTable(ManufacturerTableName);
}

void DatabaseManager::dropTable(const QString& _name)
{
	QString text ="drop table " + _name;
	QSqlQuery query(text);

	if (query.isActive() == false)
		qDebug() << "Database dropTable query" << text << endl << query.lastError().databaseText();
}

void DatabaseManager::execInitTable(const QString& _text)
{
	QSqlQuery query(_text);

	if (query.isActive() == false)
		qDebug() << "Database execInitTable query" << _text << endl  << query.lastError().databaseText();
}

}