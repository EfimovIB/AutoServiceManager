#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QTextCodec>

#include "databasemanager.h"
#include "asmapi.h"

namespace asmt
{

void DatabaseManager::initTables()
{
QString text;

text += "create table " + PersonTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "name            varchar(100),"
    "surname         varchar(100),"
    "patronymic      varchar(100)"
    ");";

text += "create table " + PhoneTableName + " ("
    "phone           varchar(20) PRIMARY KEY,"
    "idPerson        int not null"
    ");";

text += "create table " + MasterTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "idPerson        int not null,"
    "idMasterState   int not null,"
    "startDate       varchar(100) not null"
    ");";

text += "create table " + MasterStateTableName + " ("
    "id              int not null PRIMARY KEY,"
    "state           varchar(100) not null"
    ");";

for (int i = 1; i < MasterStateCount; i++)
{
    QString state = MasterStateToStr(MasterState(i));

    if (state.isEmpty() == false)
        text += "insert into " + MasterStateTableName + " (id, state) values(" + QString::number(i) + ", '" + state + "');" ;
}

text += "create table " + ManufacturerTableName + " ("
    "id              SERIAL,"
    "name            varchar(100),"
    "PRIMARY KEY     (id, name)"
    ");";

text += "create table " + SpareTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "barcode         varchar(80) not null,"
    "name            varchar(100) not null,"
    "idManufacturer  int not null,"
    "count           int default 0"
    ");";

text += "create table " + InvoiceTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "number          varchar(100) not null,"
    "date            varchar(100) not null"
    ");";

text += "create table " + InvoiceSpareTableName + " ("
    "idInvoice       int not null,"
    "idSpare         int not null,"
    "price           real not null,"
    "count           int not null,"
    "PRIMARY KEY     (idInvoice, idSpare)"
    ");";

text += "create table " + AggregateTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "name            varchar(100),"
    "number          varchar(100),"
    "idAggregateType int not null,"
    "idCar           int not null"
    ");";

text += "create table " + AggregateTypeTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "name            varchar(100) not null"
    ");";

text += "CREATE OR REPLACE FUNCTION aggregateTypeId(_name TEXT) RETURNS integer AS $$ "
        "BEGIN "
            "IF "
                "(select count(*) from " + AggregateTypeTableName + " where name=_name) = 0 "
            "THEN "
                "insert into " + AggregateTypeTableName + "(name) values(_name); "
            "END IF; "
            "RETURN  (select id from " + AggregateTypeTableName + " where name=_name); "
        "END; "
        "$$ LANGUAGE plpgsql; ";

text += "CREATE OR REPLACE FUNCTION setAggregateTypeForId(_name TEXT, _aggregateId integer) RETURNS integer AS $$ "
        "DECLARE "
            "x integer; "
        "BEGIN "
            "IF "
                "(select count(*) from " + AggregateTypeTableName + " where name=_name) = 0 "
            "THEN "
                "insert into " + AggregateTypeTableName + "(name) values(_name); "
            "END IF; "

            "IF "
                "(select count(*) from " + AggregateTableName + " where id=_aggregateId) = 0 "
            "THEN "
                "RETURN -1; "

            "ELSE "

                "x := (select id from " + AggregateTypeTableName + " where name=_name); "

                "update " + AggregateTableName + " set idAggregateType=x where id=_aggregateId; "

            "END IF; "

            "RETURN  x; "
        "END; "
        "$$ LANGUAGE plpgsql;";

text += "create table " + CarTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "name            varchar(100) not null"
    ");";

text += "create table " + ServiceStateTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "name            varchar(100) not null"
    ");";

for (int i = 1; i < ServiceStateCount; i++)
{
    QString state = ServiceStateToStr(ServiceState(i));

    if (state.isEmpty() == false)
        text += "insert into " + ServiceStateTableName + " (id, name) values(" + QString::number(i) + ", '" + state + "');" ;
}

text += "create table " + ServiceTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "idAggregate     int not null,"
    "idPerson        int not null,"
    "idMaster        int default 0,"
    "idServiceState  int not null,"
    "boxNumber       int,"
    "personComments  text,"
    "masterComments  text,"
    "changed         text,"
    "startDate       varchar(100),"
    "endDate         varchar(100),"
    "price           real"
    ");";

text += "create table " + UsedSpareTableName + " ("
    "id              SERIAL PRIMARY KEY,"
    "idService       int not null,"
    "idSpare         int not null,"
    "count           int not null,"
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

bool DatabaseManager::recalcSpareCount()
{
    QSqlDatabase::database().transaction();

    QString text = "update " + SpareTableName + " "
            "set count="
            "(select sum(count) from " + InvoiceSpareTableName + " where " + SpareTableName + ".id=" + InvoiceSpareTableName + ".idSpare) "
            "from " + InvoiceSpareTableName + " where " + SpareTableName + ".id=" + InvoiceSpareTableName + ".idSpare;"
            "update " + SpareTableName + " set count=" + SpareTableName + ".count-"
            "(select sum(count) from " + UsedSpareTableName + " where " + SpareTableName + ".id=" + UsedSpareTableName + ".idSpare) "
            "from " + UsedSpareTableName + " where " + SpareTableName + ".id=" + UsedSpareTableName + ".idSpare;";

    QSqlQuery query(text);

    if (query.isActive() == false)
    {
        qDebug() << "DatabaseManager query " << text << endl << query.lastError().databaseText();

        QSqlDatabase::database().rollback();

        return false;
    }

    QSqlDatabase::database().commit();

    return true;
}

bool DatabaseManager::execQuery(const QString& _text)
{
    QSqlDatabase::database().transaction();

    QSqlQuery query(_text);

    if (query.isActive() == false)
    {
        qDebug() << "DatabaseManager execQuery " << _text << endl << query.lastError().databaseText();

        QSqlDatabase::database().rollback();

        return false;
    }

    QSqlDatabase::database().commit();

    return true;
}

void DatabaseManager::dropTable(const QString& _name)
{
    // todo: make it in one request

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
