#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QList>
#include <QString>
#include "manufacturer.h"
#include "asmapi.h"

namespace asmt
{
static QList<Manufacturer*> Manufacturers;
static bool WasDownload = false;

Manufacturer::Manufacturer()
  : QObject()
  , m_id(-1)
{}

int Manufacturer::id() const
{
    return m_id;
}

const QString& Manufacturer::name() const
{
    return m_name;
}

Manufacturer* Manufacturer::addManufacturer(const QString& _name)
{
    Manufacturer* m = new Manufacturer;
    m->m_name = _name;
    m->m_id = biggestExistId() + 1;

    m->addInDatabase();

    checkListManufacturer();

    Manufacturers << m;
    return m;
}

const QList<Manufacturer*> Manufacturer::manufacturers()
{
    checkListManufacturer();

    return Manufacturers;
}

const Manufacturer* Manufacturer::manufacturer(int _id)
{
    checkListManufacturer();

    for (int i = 0; i < Manufacturers.size(); ++i)
        if (Manufacturers[i]->id() == _id)
            return Manufacturers[i];

    return NULL;
}

bool Manufacturer::exist(int _id)
{
    checkListManufacturer();

    for (int i = 0; i < Manufacturers.size(); ++i)
        if (Manufacturers[i]->id() == _id)
            return true;

    return false;
}

void Manufacturer::checkListManufacturer()
{
    if (WasDownload)
        return;

    downloadListManufacturer();
    WasDownload = true;
}

void Manufacturer::downloadListManufacturer()
{
    QString text = "select id, name from " + ManufacturerTableName;
    QSqlQuery query(text);
    if (query.isActive() == false)
        qDebug() << "Database service query" << text << endl << query.lastError().databaseText();

    for (;query.next();)
    {
        Manufacturer* s = new Manufacturer;
        s->m_id = query.value(0).toInt();
        s->m_name = query.value(1).toString();
        Manufacturers << s;
    }
}

int Manufacturer::biggestExistId()
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

void Manufacturer::addInDatabase()
{
    QString text = "insert into " + ManufacturerTableName + "   values(" + QString::number(m_id) + ", '" + m_name + "')";
    QSqlQuery query(text);

    if (query.isActive() == false)
        qDebug() << "Manufacturer addInDatabase query" << text << endl << query.lastError().databaseText ();
}

}
