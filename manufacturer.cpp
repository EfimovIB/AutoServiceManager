#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QList>
#include <QString>
#include "manufacturer.h"
#include "asmapi.h"

namespace asmt
{
static QList<Manufacturer_old*> Manufacturers;
static bool WasDownload = false;

Manufacturer_old::Manufacturer_old()
  : QObject()
  , m_id(-1)
{}

int Manufacturer_old::id() const
{
    return m_id;
}

const QString& Manufacturer_old::name() const
{
    return m_name;
}

Manufacturer_old* Manufacturer_old::addManufacturer(const QString& _name)
{
    Manufacturer_old* m = new Manufacturer_old;
    m->m_name = _name;
    m->m_id = biggestExistId() + 1;

    m->addInDatabase();

    checkListManufacturer();

    Manufacturers << m;
    return m;
}

const QList<Manufacturer_old*> Manufacturer_old::manufacturers()
{
    checkListManufacturer();

    return Manufacturers;
}

const Manufacturer_old* Manufacturer_old::manufacturer(int _id)
{
    checkListManufacturer();

    for (int i = 0; i < Manufacturers.size(); ++i)
        if (Manufacturers[i]->id() == _id)
            return Manufacturers[i];

    return NULL;
}

bool Manufacturer_old::exist(int _id)
{
    checkListManufacturer();

    for (int i = 0; i < Manufacturers.size(); ++i)
        if (Manufacturers[i]->id() == _id)
            return true;

    return false;
}

void Manufacturer_old::checkListManufacturer()
{
    if (WasDownload)
        return;

    downloadListManufacturer();
    WasDownload = true;
}

void Manufacturer_old::downloadListManufacturer()
{
    QString text = "select id, name from " + ManufacturerTableName;
    QSqlQuery query(text);
    if (query.isActive() == false)
        qDebug() << "Database service query" << text << endl << query.lastError().databaseText();

    for (;query.next();)
    {
        Manufacturer_old* s = new Manufacturer_old;
        s->m_id = query.value(0).toInt();
        s->m_name = query.value(1).toString();
        Manufacturers << s;
    }
}

int Manufacturer_old::biggestExistId()
{
    checkListManufacturer();

    if (Manufacturers.isEmpty())
        return 0;

    int biggest = Manufacturers.first()->id();

    for (int i = 1; i < Manufacturers.size(); ++i)
        if (Manufacturers[i]->id() > biggest)
            biggest = Manufacturers[i]->id();

    return biggest;
}

void Manufacturer_old::addInDatabase()
{
    QString text = "insert into " + ManufacturerTableName + "   values(" + QString::number(m_id) + ", '" + m_name + "')";
    QSqlQuery query(text);

    if (query.isActive() == false)
        qDebug() << "Manufacturer addInDatabase query" << text << endl << query.lastError().databaseText ();
}

}
