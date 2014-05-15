#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "datastructs.h"

namespace asmt
{

QList<Person> Person::persons()
{
    return QList<Person>();
}

QStringList Person::phones(unsigned int _idPerson)
{
    QStringList l;

    QString text = "select phone from " + PhoneTableName + " where idPerson = " + QString::number(_idPerson);

    QSqlQuery query(text);

    if (query.isActive() == false)
    {
        qDebug() << "Phones query " << text << endl << query.lastError().databaseText();

        return l;
    }

    for (;query.next();)
    {
        l << query.value(0).toString();
    }

    return l;
}

QList<QSharedPointer<Master>> Master::masters()
{
    QList<QSharedPointer<Master>> l;

    QString text = "select "
            " Person.id as idPerson"
           ", Masters.id as idMasters"
           ", Person.name as name"
           ", Person.surname as surname"
           ", Person.patronymic as patronymic"
           ", Masters.idMasterState as state"
           ", Masters.startDate as startDate"
           " from " + PersonTableName + ", " + MasterTableName +
           " where " + PersonTableName + ".id = " + MasterTableName + ".idPerson ";

    QSqlQuery query(text);

    if (query.isActive() == false)
    {
        qDebug() << "Masters query " << text << endl << query.lastError().databaseText();

        return l;
    }

    for (;query.next();)
    {
        QSharedPointer<Master> m = QSharedPointer<Master>(new Master);

        m->person.id         = query.value(0).toInt();
        m->id                = query.value(1).toInt();
        m->person.name       = query.value(2).toString();
        m->person.surname    = query.value(3).toString();
        m->person.patronymic = query.value(4).toString();
        m->state             = MasterState(query.value(5).toInt());
        m->date              = QDate::fromString(query.value(6).toString(), DbDateFormat);
        m->person.phone     = Person::phones(m->person.id);

        l << m;
    }

    return l;
}

bool Spare::insertInDatabase()
{
    if (manufacturer.insertInDatabase() == false)
        return false;

    QString text = "select id, idManufacturer from " + SpareTableName + " where barcode='" + barcode + "' and name='" + name + "'";

    QSqlQuery query(text);

    if (query.isActive() == false)
    {
        qDebug() << "Spare query " << text << endl << query.lastError().databaseText();

        return false;
    }

    if (query.next() && query.value(1).toUInt() == manufacturer.id)
    {
        id = query.value(0).toUInt();

        return true;
    }

    text = "insert into " + SpareTableName + "(barcode, name, idManufacturer) values("
            "'" + barcode + "'"
          ", '" + name + "'"
           ", " + QString::number(manufacturer.id) + ")";

    query.exec(text);

    if (query.isActive() == false)
    {
        qDebug() << "Spare query " << text << endl << query.lastError().databaseText();

        return false;
    }

    text = "select id from " + SpareTableName + " where barcode='" + barcode + "' and name='" + name + "' and idManufacturer=" + manufacturer.id;

    query.exec(text);

    if (query.isActive() == false || query.next() == false)
    {
        qDebug() << "Spare query " << text << endl << query.lastError().databaseText();

        return false;
    }

    id = query.value(0).toUInt();

    return true;
}

QList<QSharedPointer<Spare> > Spare::spares(const QString& _barcode)
{
    QList<QSharedPointer<Spare>> l;

    // todo

    return l;
}

bool Manufacturer::insertInDatabase()
{
    QString text = "select id from " + ManufacturerTableName + " where name='" + name + "'";

    QSqlQuery query(text);

    if (query.isActive() == false)
    {
        qDebug() << "Manufacturer query " << text << endl << query.lastError().databaseText();

        return false;
    }

    if (query.next())
    {
        id = query.value(0).toUInt();

        return true;
    }

    text = "insert into " + ManufacturerTableName + "(name) values('" + name + "')";

    query.exec(text);

    if (query.isActive() == false)
    {
        qDebug() << "Manufacturer query " << text << endl << query.lastError().databaseText();

        return false;
    }

    text = "select id from " + ManufacturerTableName + " where name='" + name + "'";

    query.exec(text);

    if (query.isActive() == false || query.next() == false)
    {
        qDebug() << "Manufacturer query " << text << endl << query.lastError().databaseText();

        return false;
    }

    id = query.value(0).toUInt();

    return true;
}

bool Invoice::insertInDatabase()
{
    if (id) return true;

    QString text = "select id from " + InvoiceTableName + " where number='" + number + "' and date='" + date.toString(DbDateFormat) + "'";

    QSqlQuery query(text);

    if (query.isActive() == false)
    {
        qDebug() << "Invoice query " << text << endl << query.lastError().databaseText();

        return false;
    }

    if (query.next())
    {
        id = query.value(0).toUInt();

        return true;
    }

    text = "insert into " + InvoiceTableName + "(number, date) values("
                              "'" + number + "'"
                            ", '" + date.toString(DbDateFormat) + "')";

    query.exec(text);

    if (query.isActive() == false)
    {
        qDebug() << "Invoice query " << text << endl << query.lastError().databaseText();

        return false;
    }

    text = "select id from " + InvoiceTableName + " where number='" + number + "' and date='" + date.toString(DbDateFormat) + "'";

    query.exec(text);

    if (query.isActive() == false || query.next() == false)
    {
        qDebug() << "Invoice query " << text << endl << query.lastError().databaseText();

        return false;
    }

    id = query.value(0).toUInt();

    return true;
}

bool InvoiceSpare::insertInDatabase()
{
    if (invoice->insertInDatabase() == false || spare.insertInDatabase() == false)
        return false;

    QString text = "select * from " + InvoiceSpareTableName + " where idInvoice=" + QString::number(invoice->id) + " and idSpare=" + QString::number(spare.id);

    QSqlQuery query(text);

    if (query.isActive() == false)
    {
        qDebug() << "InvoiceSpare query " << text << endl << query.lastError().databaseText();

        return false;
    }

    if (query.next())
    {
        text = "update " + InvoiceSpareTableName +
               " set price=" + QString::number(price) + ", count=" + QString::number(count) +
               " where idInvoice=" + QString::number(invoice->id) + " and idSpare=" + QString::number(spare.id);
    }
    else
    {
        text = "insert into " + InvoiceSpareTableName + "(idInvoice, idSpare, price, count) values("
                                ", " + QString::number(invoice->id) +
                                ", " + QString::number(spare.id) +
                                ", " + QString::number(price) +
                                ", " + QString::number(count) + ")";
    }

    query.exec(text);

    if (query.isActive() == false)
    {
        qDebug() << "InvoiceSpare query " << text << endl << query.lastError().databaseText();

        return false;
    }

    return true;
}

}
