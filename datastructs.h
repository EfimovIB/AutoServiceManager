#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#include <QStringList>
#include <QDate>
#include <QSharedPointer>
#include <QPair>

#include "asmapi.h"

namespace asmt
{
    struct Person
    {
        Person() : id(0) {}

        unsigned int id;
        QString name;
        QString surname;
        QString patronymic;
        QStringList phone;

        static QList<Person> persons();
        static QStringList phones(unsigned int _idPerson);
    };

    struct Master
    {
        Master() : id(0) {}

        unsigned int id;
        Person person;
        MasterState state;
        QDate date;

        static QList<QSharedPointer<Master>> masters();
    };

    struct Invoice
    {
        Invoice() : id(0) {}

        unsigned int id; // todo hide id in private
        QString number;
        QDate date;

        bool insertInDatabase();
    };

    struct Manufacturer
    {
        Manufacturer(unsigned int _id = 0, const QString& _name = QString()) : id(_id), name(_name) {}

        unsigned int id;
        QString name;

        bool insertInDatabase();
    };

    struct Spare
    {
        Spare() : id(0) {}

        unsigned int id;
        Manufacturer  manufacturer;
        QString barcode;
        QString name;

        bool insertInDatabase();

        static QList<QSharedPointer<Spare>> spares();
        static QList<QSharedPointer<Spare>> spares(const QString& _barcode); // todo
        static QList<QSharedPointer<QPair<Spare, quint32> > > wareHouse();
    };

    struct InvoiceSpare
    {
        InvoiceSpare() : invoice(NULL), price(0), count(0) {}

        QSharedPointer<Invoice> invoice;
        Spare spare;
        qreal price;
        unsigned int count;

        bool insertInDatabase();
    };
}

#endif // DATASTRUCTS_H
