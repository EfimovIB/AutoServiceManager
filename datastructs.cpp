#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "datastructs.h"

namespace asmt
{

bool Person::insertInDatabase()
{
    QString text;

    text = "select idPerson from " + PhoneTableName + " where "; // todo phones could be the same. We shell have had ways to change the owner of phone number.

    for (int i = 0; i < phone.size(); i++) // todo every time before inserting shell check phone number must be!
    {
        text += "phone='" + phone[i] + "'";

        if (i < phone.size()-1)
            text += " or ";
    }

    // todo the phone numbers should has got one format

    QSqlQuery query(text);

    if (query.isActive() == false)
    {
        qDebug() << "Person query " << text << endl << query.lastError().databaseText();

        return false;
    }

    if (query.next()) // todo name, surname, patronymic should have one format
    {
        unsigned int idPerson = query.value(0).toUInt();

        text = "select name, surname, patronymic from " + PersonTableName + " where id=" + QString::number(idPerson);

        query.exec(text);

        if (query.isActive() == false || query.next() == false)
        {
            qDebug() << "Person query " << text << endl << query.lastError().databaseText();

            return false;
        }

        QString nameDb = query.value(0).toString();
        QString surnameDb = query.value(1).toString();
        QString patronymicDb = query.value(2).toString();

        bool res = true;

        // todo if one of db values is empty then update it

        if (name != nameDb && !name.isEmpty() && !nameDb.isEmpty())
            return false;

        if (surname != surnameDb && !surname.isEmpty() && !surnameDb.isEmpty())
            return false;

        if (patronymic != patronymicDb && !patronymic.isEmpty() && !patronymicDb.isEmpty())
            return false;

        id = idPerson;

        return true;
    }

    text = "insert into " + PersonTableName + "(name, surname, patronymic) values("
                      "'" + name + "'"
                    ", '" + surname + "'"
                    ", '" + patronymic + "') returning id";

    query.exec(text);

    if (query.isActive() == false || query.next() == false)
    {
        qDebug() << "Person insertDataInDatabase query " << text << endl << query.lastError().databaseText();

        return false;
    }

    id = query.value(0).toUInt();

    text = "insert into " + PhoneTableName + " values("
                      "'" + phone.first() + "'" // todo phones coount could be more than one
                      ", " + QString::number(id) + ")";

// todo check all db request on 'select max(id) from'/ There is could be error. Better way is 'returning id'

    query.exec(text);

    if (query.isActive() == false)
    {
        qDebug() << "Person insertDataInDatabase query " << text << endl << query.lastError().databaseText();

        return false;
    }

    return true;
}

QList<QSharedPointer<Person> > Person::persons()
{
    return QList<QSharedPointer<Person> >(); // todo
}

QList<QSharedPointer<Person> > Person::persons(const QString& _phone)
{
    return QList<QSharedPointer<Person> >(); // todo
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

QList<QSharedPointer<Master> > Master::masters()
{
    QList<QSharedPointer<Master> > l;

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

    text = "select id from " + SpareTableName + " where barcode='" + barcode + "' and name='" + name + "' and idManufacturer=" + QString::number(manufacturer.id);

    query.exec(text);

    if (query.isActive() == false || query.next() == false)
    {
        qDebug() << "Spare query " << text << endl << query.lastError().databaseText();

        return false;
    }

    id = query.value(0).toUInt();

    return true;
}

QList<QSharedPointer<Spare> > Spare::spares()
{
    QList<QSharedPointer<Spare> > l;

    QString text = "select "
                    + SpareTableName + ".id"
               ", " + SpareTableName + ".barcode"
               ", " + SpareTableName + ".name"
               ", " + SpareTableName + ".count"
               ", " + SpareTableName + ".idManufacturer"
               ", " + ManufacturerTableName + ".name "
           " from " + SpareTableName + ", " + ManufacturerTableName +
           " where " + ManufacturerTableName + ".id = " + SpareTableName + ".idManufacturer ";

    QSqlQuery query(text);

    if (query.isActive() == false)
    {
        qDebug() << "Spares query " << text << endl << query.lastError().databaseText();

        return l;
    }

    for (;query.next();)
    {
        QSharedPointer<Spare> s = QSharedPointer<Spare>(new Spare);

        s->id            = query.value(0).toUInt();
        s->barcode       = query.value(1).toString();
        s->name          = query.value(2).toString();
        s->count         = query.value(3).toUInt();
        s->manufacturer  = Manufacturer(query.value(4).toUInt(), query.value(5).toString());

        l << s;
    }

    return l;
}

QList<QSharedPointer<Spare> > Spare::spares(const QString& _barcode)
{
    QList<QSharedPointer<Spare> > l;

    QString text = "select "
                    + SpareTableName + ".id"
               ", " + SpareTableName + ".barcode"
               ", " + SpareTableName + ".name"
               ", " + SpareTableName + ".count"
               ", " + SpareTableName + ".idManufacturer"
               ", " + ManufacturerTableName + ".name "
           " from " + SpareTableName + ", " + ManufacturerTableName +
           " where " + ManufacturerTableName + ".id = " + SpareTableName + ".idManufacturer and " + SpareTableName + ".barcode=" + _barcode;

    QSqlQuery query(text);

    if (query.isActive() == false)
    {
        qDebug() << "Spares query " << text << endl << query.lastError().databaseText();

        return l;
    }

    for (;query.next();)
    {
        QSharedPointer<Spare> s = QSharedPointer<Spare>(new Spare);

        s->id            = query.value(0).toUInt();
        s->barcode       = query.value(1).toString();
        s->name          = query.value(2).toString();
        s->count         = query.value(3).toUInt();
        s->manufacturer  = Manufacturer(query.value(4).toUInt(), query.value(5).toString());

        l << s;
    }

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

    QString text = "select count from " + InvoiceSpareTableName + " where idInvoice=" + QString::number(invoice->id) + " and idSpare=" + QString::number(spare.id);

    QSqlQuery query(text);

    if (query.isActive() == false)
    {
        qDebug() << "InvoiceSpare query " << text << endl << query.lastError().databaseText();

        return false;
    }

    if (query.next())
    {
        unsigned int delta = count - query.value(0).toUInt();

        text = "update " + InvoiceSpareTableName +
               " set price=" + QString::number(price) + ", count=" + QString::number(count) +
               " where idInvoice=" + QString::number(invoice->id) + " and idSpare=" + QString::number(spare.id) +
               "; update " + SpareTableName + " set count=count+" + QString::number(delta) + " where id=" + QString::number(spare.id) + ";";
    }
    else
    {
        text = "insert into " + InvoiceSpareTableName + "(idInvoice, idSpare, price, count) values("
                                     + QString::number(invoice->id) +
                                ", " + QString::number(spare.id) +
                                ", " + QString::number(price) +
                                ", " + QString::number(count) + ");" +
                "update " + SpareTableName + " set count=count+" + QString::number(count) + " where id=" + QString::number(spare.id) + ";";
    }

    query.exec(text);

    if (query.isActive() == false)
    {
        qDebug() << "InvoiceSpare query " << text << endl << query.lastError().databaseText();

        return false;
    }

    return true;
}

bool AggregateType::insertInDatabase()
{
    if (id != 0)
        return true;

    QString text = "select id from " + AggregateTypeTableName + " where name='" + name + "'";

    QSqlQuery query(text);

    if (query.isActive() == false)
    {
        qDebug() << "AggregateType query " << text << endl << query.lastError().databaseText();

        return false;
    }

    if (query.next())
    {
        id = query.value(0).toUInt();

        return true;
    }

    text = "insert into " + AggregateTypeTableName + "(name) values('" + name + "') returning id";

    query.exec(text);

    if (query.isActive() == false || query.next() == false)
    {
        qDebug() << "AggregateType query " << text << endl << query.lastError().databaseText();

        return false;
    }

    id = query.value(0).toUInt();

    return true;
}

bool Car::insertInDatabase()
{
    if (id != 0)
        return true;

    QString text = "select id from " + CarTableName + " where name='" + name + "'";

    QSqlQuery query(text);

    if (query.isActive() == false)
    {
        qDebug() << "Car query " << text << endl << query.lastError().databaseText();

        return false;
    }

    if (query.next())
    {
        id = query.value(0).toUInt();

        return true;
    }

    text = "insert into " + AggregateTypeTableName + "(name) values('" + name + "') returning id";

    query.exec(text);

    if (query.isActive() == false || query.next() == false)
    {
        qDebug() << "Car query " << text << endl << query.lastError().databaseText();

        return false;
    }

    id = query.value(0).toUInt();

    return true;
}

bool Aggregate::insertInDatabase()
{
    if (type.insertInDatabase() == false || car.insertInDatabase() == false)
        return false;

    if (id != 0)
        return true;

    QString text = "select id from " + AggregateTableName + " where "
                          + "name='" + name + "'" +
                   + " and number='" + number + "'" +
           + " and idAggregateType=" + QString::number(type.id) +
                     + " and idCar=" + QString::number(car.id);

    QSqlQuery query(text);

    if (query.isActive() == false)
    {
        qDebug() << "Agregate query " << text << endl << query.lastError().databaseText();

        return false;
    }

    if (query.next())
    {
        id = query.value(0).toUInt();

        return true;
    }

    text = "insert into " + AggregateTableName + "(name, number, idAggregateType, idCar) values("
                             "'" + name + "'" +
                           ", '" + number + "'" +
                            ", " + QString::number(type.id) +
                            ", " + QString::number(car.id) + ") returning id";

    query.exec(text);

    if (query.isActive() == false || query.next() == false)
    {
        qDebug() << "Agregate query " << text << endl << query.lastError().databaseText();

        return false;
    }

    id = query.value(0).toUInt();

    return true;
}

}
