#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "datastructs.h"

namespace asmt
{

bool Person::isValid() const
{
    return phone.isEmpty() == false && (name.isEmpty() == false || surname.isEmpty() == false || patronymic.isEmpty() == false);
}

bool Person::insertInDatabase()
{
    if (id != 0)
        return true;

    if (isValid() == false)
    {
        qDebug() << "Person is invalid";

        return false;
    }

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
                      "'" + phone.first() + "'" // todo phones count could be more than one
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

QSharedPointer<Person> Person::person(unsigned int _id)
{
    QSharedPointer<Person> p(NULL);

    if (_id <= 0)
        return p;

    QString text = "select "
                            + PersonTableName + ".name"
                       ", " + PersonTableName + ".surname"
                       ", " + PersonTableName + ".patronymic"
                       ", " + PhoneTableName + ".phone"
                   " from "
                            + PersonTableName +
                       ", " + PhoneTableName +
                  " where " + PhoneTableName + ".idPerson=" + PersonTableName + ".id"
                    " and " + PersonTableName + ".id = " + QString::number(_id);


    QSqlQuery query(text);

    if (query.isActive() == false || query.next() == false)
    {
        qDebug() << "Person query " << text << endl << query.lastError().databaseText();

        return p;
    }

    p = QSharedPointer<Person>(new Person);

    p->id = _id;
    p->name = query.value(0).toString();
    p->surname = query.value(1).toString();
    p->patronymic = query.value(2).toString();
    p->phone.append(query.value(3).toString());

    for(;query.next();)
    {
        p->phone.append(query.value(3).toString());
    }

    return p;

}

QMap<int, QSharedPointer<Person> > Person::persons()
{
    QMap<int, QSharedPointer<Person> > m;

    QString text = "select "
                 + PersonTableName + ".id"
            ", " + PersonTableName + ".name"
            ", " + PersonTableName + ".surname"
            ", " + PersonTableName + ".patronymic"
            ", " + PhoneTableName + ".phone"
            " from "
             + PersonTableName +
            ", " + PhoneTableName +
            " where "
            + PersonTableName + ".id=" + PhoneTableName + ".idPerson";

    QSqlQuery query(text);

    if (query.isActive() == false)
    {
        qDebug() << "Person query " << text << endl << query.lastError().databaseText();

        return m;
    }

    for (;query.next();)
    {
        QMap<int, QSharedPointer<Person> >::iterator it = m.find(query.value(0).toInt());

        if (it == m.end())
        {
            QSharedPointer<Person> p = QSharedPointer<Person>(new Person);

            p->id = query.value(0).toInt();
            p->name = query.value(1).toString();
            p->surname = query.value(2).toString();
            p->patronymic = query.value(3).toString();
            p->phone << query.value(4).toString();

            m[p->id] = p;
        }
        else
        {
            it->value->phone << query.value(4).toString();
        }
    }

    return m;
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

bool Master::isValid() const
{
    return person.isValid() && state == Works;
}

bool Master::insertInDatabase()
{
    if (id != 0)
        return true;

    if (person.insertInDatabase() == false)
        return false;

    QString text = "select id from " + MasterTableName + " where idPerson=" + QString::number(person.id);

    QSqlQuery query(text);

    if (query.isActive() == false)
    {
        qDebug() << "Master query " << text << endl << query.lastError().databaseText();

        return false;
    }

    if (query.next())
    {
        id = query.value(0).toUInt();

        return true;
    }

    text = "insert into " + MasterTableName + "(idPerson, idMasterState, startDate) values("
                          + QString::number(person.id) +
                     ", " + QString::number(state) +
                    ", '" + date.toString(DbDateFormat)+ "') returning id";

    query.exec(text);

    if (query.isActive() == false || query.next() == false)
    {
        qDebug() << "Master query " << text << endl << query.lastError().databaseText();

        return false;
    }

    id = query.value(0).toUInt();

    return true;
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

QSharedPointer<Master> Master::master(unsigned int _id)
{
    QSharedPointer<Master> m(NULL);

    if (_id <= 0)
        return m;

    QString text = "select "
            " Person.id as idPerson"
           ", Masters.id as idMasters"
           ", Person.name as name"
           ", Person.surname as surname"
           ", Person.patronymic as patronymic"
           ", Masters.idMasterState as state"
           ", Masters.startDate as startDate"
           " from " + PersonTableName + ", " + MasterTableName +
           " where " + MasterTableName + ".id = " + QString::number(_id) +
           " and " + MasterTableName + ".idPerson = " + PersonTableName + ".id";

    QSqlQuery query(text);

    if (query.isActive() == false || query.next() == false)
    {
        qDebug() << "Masters query " << text << endl << query.lastError().databaseText();

        return m;
    }

    m = QSharedPointer<Master>(new Master);

    m->person.id         = query.value(0).toInt();
    m->id                = query.value(1).toInt();
    m->person.name       = query.value(2).toString();
    m->person.surname    = query.value(3).toString();
    m->person.patronymic = query.value(4).toString();
    m->state             = MasterState(query.value(5).toInt());
    m->date              = QDate::fromString(query.value(6).toString(), DbDateFormat);
    m->person.phone     = Person::phones(m->person.id);

    return m;
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

    text = "insert into " + ManufacturerTableName + "(name) values('" + name + "') returning id";

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
                            ", '" + date.toString(DbDateFormat) + "') returning id";

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

    text = "insert into " + CarTableName + "(name) values('" + name + "') returning id";

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

QSharedPointer<Aggregate> Aggregate::aggregate(unsigned int _id)
{
    QSharedPointer<Aggregate> a(NULL);

    if (_id <= 0)
        return a;

    QString text = "select "
                          + AggregateTableName + ".name"
                     ", " + AggregateTableName + ".number"
                     ", " + AggregateTypeTableName + ".id"
                     ", " + AggregateTypeTableName + ".name"
                     ", " + CarTableName + ".id"
                     ", " + CarTableName + ".name"
                " from "
                          + AggregateTableName +
                     ", " + AggregateTypeTableName +
                     ", " + CarTableName +
                " where "
                          + AggregateTableName + ".id=1"
                  " and " + AggregateTypeTableName + ".id=" + AggregateTableName + ".idAggregateType"
                  " and " + CarTableName + ".id=" + AggregateTableName + ".idCar";

    QSqlQuery query(text);

    if (query.isActive() == false || query.next() == false)
    {
        qDebug() << "Aggregate query " << text << endl << query.lastError().databaseText();

        return a;
    }

    a = QSharedPointer<Aggregate>(new Aggregate);

    a->id = _id;
    a->name = query.value(0).toString();
    a->number = query.value(1).toString();
    a->type.id = query.value(2).toInt();
    a->type.name = query.value(3).toString();
    a->car.id = query.value(4).toInt();
    a->car.name = query.value(5).toString();

    return a;
}

bool Service::insertInDatabase()
{
    if (id != 0)
        return true;

    if (aggregate.insertInDatabase() == false
      || person.insertInDatabase() == false
      || (master.isValid() && master.insertInDatabase() == false))
        return false;

    QString text = "insert into " + ServiceTableName
            + "(idAggregate, idPerson, idMaster, idServiceState, boxNumber, personComments, masterComments, changed, startDate, endDate, price) values("
                              + QString::number(aggregate.id) +
                         ", " + QString::number(person.id) +
                         ", " + QString::number(master.id) +
                         ", " + QString::number(state) +
                         ", " + QString::number(boxNumber) +
                        ", '" + personComments + "'"
                        ", '" + mastersComments + "'"
                        ", '" + changed + "'"
                        ", '" + startDate.toString(DbDateFormat) + "'"
                        ", '" + endDate.toString(DbDateFormat) + "'"
                         ", " + QString::number(price) + ") returning id";


    QSqlQuery query(text);

    if (query.isActive() == false || query.next() == false)
    {
        qDebug() << "Service query " << text << endl << query.lastError().databaseText();

        return false;
    }

    id = query.value(0).toUInt();

    return true;
}

QSharedPointer<Service> Service::service(unsigned int _id)
{
    QSharedPointer<Service> s(NULL);

    if (_id <= 0)
        return s;

    QString text = "select "
          + ServiceTableName + ".idAggregate"
     ", " + ServiceTableName + ".idPerson"
     ", " + ServiceTableName + ".idMaster"
     ", " + ServiceTableName + ".idServiceState"
     ", " + ServiceTableName + ".boxNumber"
     ", " + ServiceTableName + ".personComments"
     ", " + ServiceTableName + ".masterComments"
     ", " + ServiceTableName + ".changed"
     ", " + ServiceTableName + ".startDate"
     ", " + ServiceTableName + ".endDate"
     ", " + ServiceTableName + ".price"
     " from " + ServiceTableName + " where " + ServiceTableName + ".id = " + QString::number(_id);

    QSqlQuery query(text);

    if (query.isActive() == false || query.next() == false)
    {
        qDebug() << "Service query " << text << endl << query.lastError().databaseText();

        return s;
    }

    s = QSharedPointer<Service>(new Service);

    unsigned int idAggregate = query.value(0).toUInt();
    unsigned int idPerson = query.value(1).toUInt();
    unsigned int idMaster = query.value(2).toUInt();

    s->id = _id;
    s->state = ServiceState(query.value(3).toInt());
    s->boxNumber = query.value(4).toUInt();
    s->personComments = query.value(5).toString();
    s->mastersComments = query.value(6).toString();
    s->changed = query.value(7).toString();
    s->startDate = QDate::fromString(query.value(8).toString(), DbDateFormat);
    s->endDate = QDate::fromString(query.value(9).toString(), DbDateFormat);
    s->price = query.value(10).toFloat();

    QSharedPointer<Person> p = Person::person(idPerson);

    if (p)
    {
        s->person = *p;
    }

    QSharedPointer<Master> m = Master::master(idMaster);

    if (m)
    {
        s->master = *m;
    }

    QSharedPointer<Aggregate> a = Aggregate::aggregate(idAggregate);

    if (a)
    {
        s->aggregate = *a;
    }

    return s;
}

QList<QSharedPointer<Service> > Service::service()
{
    QList<QSharedPointer<Service> > l;

//    QString text = "select "
//                    + SpareTableName + ".id"
//               ", " + SpareTableName + ".barcode"
//               ", " + SpareTableName + ".name"
//               ", " + SpareTableName + ".count"
//               ", " + SpareTableName + ".idManufacturer"
//               ", " + ManufacturerTableName + ".name "
//           " from " + SpareTableName + ", " + ManufacturerTableName +
//           " where " + ManufacturerTableName + ".id = " + SpareTableName + ".idManufacturer ";

//    QSqlQuery query(text);

//    if (query.isActive() == false)
//    {
//        qDebug() << "Spares query " << text << endl << query.lastError().databaseText();

//        return l;
//    }

//    for (;query.next();)
//    {
//        QSharedPointer<Spare> s = QSharedPointer<Spare>(new Spare);

//        s->id            = query.value(0).toUInt();
//        s->barcode       = query.value(1).toString();
//        s->name          = query.value(2).toString();
//        s->count         = query.value(3).toUInt();
//        s->manufacturer  = Manufacturer(query.value(4).toUInt(), query.value(5).toString());

//        l << s;
//    }

    return l;
}

QList<QSharedPointer<SimplifyService> > SimplifyService::service()
{
    QList<QSharedPointer<SimplifyService> > l;

    QString text = "select "
          + ServiceTableName + ".id"
     ", " + ServiceTableName + ".idServiceState"
     ", " + ServiceTableName + ".boxNumber"
     ", " + ServiceTableName + ".startDate"
     ", " + ServiceTableName + ".endDate"
     ", " + AggregateTableName + ".name"
     ", " + PersonTableName + ".name"
     ", " + PersonTableName + ".patronymic as personPatronymic"
         " from " + ServiceTableName + ", " + AggregateTableName + ", " + PersonTableName +
         " where "
                  + AggregateTableName + ".id = " + ServiceTableName + ".idAggregate"
         " and "  + PersonTableName + ".id = " + ServiceTableName + ".idPerson";

    QSqlQuery query(text);

    if (query.isActive() == false)
    {
        qDebug() << "SimplifyService query " << text << endl << query.lastError().databaseText();

        return l;
    }

    for (;query.next();)
    {
        QSharedPointer<SimplifyService> s = QSharedPointer<SimplifyService>(new SimplifyService);

        s->id = query.value(0).toUInt();
        s->state = ServiceState(query.value(1).toInt());
        s->boxNumber = query.value(2).toUInt();
        s->startDate = QDate::fromString(query.value(3).toString(), DbDateFormat);
        s->endDate = QDate::fromString(query.value(4).toString(), DbDateFormat);
        s->aggregateName = query.value(5).toString();
        s->personName = query.value(6).toString();
        s->personPatronymic = query.value(7).toString();

        l << s;
    }

    return l;
}

}
