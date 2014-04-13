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

text = "create table " + PersonTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "name            varchar(100),"
    "surname         varchar(100),"
    "patronymic      varchar(100)"
    ");";

execInitTable(text);

text = "create table " + PhoneTableName + " ("
    "phone           varchar(20) PRIMARY KEY,"
    "idPerson        int not null"
    ");";

execInitTable(text);

text = "create table " + MasterTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "idPerson        int not null,"
    "idMasterState   int not null,"
    "startDate       varchar(100) not null"
    ");";

execInitTable(text);

text = "create table " + MasterStateTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "state           varchar(100) not null"
    ");";

execInitTable(text);

text = "create table " + ManufacturerTableName + " ("
    "id              SERIAL,"
    "name            varchar(100),"
    "PRIMARY KEY     (id, name)"
    ");";

execInitTable(text);

text = "create table " + SpareTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "barcode         varchar(80) not null,"
    "name            varchar(100) not null,"
    "idManufacturer  int not null"
    ");";

execInitTable(text);

text = "create table " + InvoiceTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "number          varchar(100) not null,"
    "date            varchar(100) not null"
    ");";

execInitTable(text);

text = "create table " + InvoiceSpareTableName + " ("
    "idInvoice       int not null,"
    "idSpare         int not null,"
    "price           real not null,"
    "count           int not null"
    ");";

execInitTable(text);

text = "create table " + AggregateTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "name            varchar(100),"
    "number          varchar(100),"
    "idAggregateType int not null,"
    "idCar           int not null"
    ");";

execInitTable(text);

text = "create table " + AggregateTypeTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "name            varchar(100) not null"
    ");";

execInitTable(text);

text = "create table " + CarTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "name            varchar(100) not null"
    ");";

execInitTable(text);

text = "create table " + ServiceStateTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "name            varchar(100) not null"
    ");";

execInitTable(text);

text = "create table " + ServiceTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "idAggregate     int not null,"
    "idPerson        int not null,"
    "idMaster        int not null,"
    "idServiceState  int not null,"
    "boxNumber       int,"
    "personComments  text,"
    "masterComments  text,"
    "changed         text,"
    "startDate       varchar(100),"
    "endDate         varchar(100),"
    "price           real"
    ");";

execInitTable(text);

text = "create table " + UsedSpareTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "idService       int not null,"
    "idSpare         int not null,"
    "comments        text,"
    "date            varchar(100) not null"
    ");";

execInitTable(text);
}

void DatabaseManager::dropTables()
{
    dropTable(PersonTableName);
    dropTable(PhoneTableName);
    dropTable(MasterTableName);
    dropTable(MasterStateTableName);
    dropTable(ManufacturerTableName);
    dropTable(SpareTableName);
    dropTable(InvoiceTableName);
    dropTable(InvoiceSpareTableName);
    dropTable(AggregateTableName);
    dropTable(AggregateTypeTableName);
    dropTable(CarTableName);
    dropTable(ServiceStateTableName);
    dropTable(ServiceTableName);
    dropTable(UsedSpareTableName);
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
