#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

#include "databasemanager.h"
#include "asmapi.h"

namespace asmt
{

void DatabaseManager::initTables()
{
	QString text;

	text = "create table " + WarehouseTableName + " ("
		"barcode       varchar(80) not null,"
		"name          varchar(100),"
		"manufacturer  int,"
		"count         int"
		");";

	execInitTable(text);
	
	text = "create table " + ManufacturerTableName + " ("
		"id            int not null,"
		"name          varchar(100)"
		");";

	execInitTable(text);

	text = "create table " + PersonTableName + " ("
		"id            varchar(100) not null,"
		"name          varchar(100),"
		"surname       varchar(100),"
		"patronymic    varchar(100),"
		"phones        text,"
		"type          int"
		");";

	execInitTable(text);

	text = "create table " + ServiceTableName + " ("
		"id                    varchar(100) not null,"
		"clientId             varchar(100),"
		"masterId             varchar(100),"
		"clientComments       text,"
		"masterComments       text,"
		"changed               text,"
		"startDate             varchar(100),"
		"endDate               varchar(100),"
		"price                 real"
		");";

	execInitTable(text);
}

void DatabaseManager::dropTables()
{
	dropTable(WarehouseTableName);
	dropTable(ManufacturerTableName);
	dropTable(PersonTableName);
	dropTable(ServiceTableName);
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