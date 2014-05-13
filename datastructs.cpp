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

QList<QSharedPointer<Spare> > Spare::spares(const QString& _barcode)
{
    QList<QSharedPointer<Spare>> l;

    // todo

    return l;
}

}
