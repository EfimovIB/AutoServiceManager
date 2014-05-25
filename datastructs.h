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

        bool insertInDatabase();

        static QList<QSharedPointer<Person> > persons();
        static QList<QSharedPointer<Person> > persons(const QString& _phone);
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
        Spare() : id(0), count(0) {}

        unsigned int id;
        Manufacturer  manufacturer;
        QString barcode;
        QString name;
        unsigned int count;

        bool insertInDatabase();

        static QList<QSharedPointer<Spare>> spares();
        static QList<QSharedPointer<Spare>> spares(const QString& _barcode); // todo
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

    struct AggregateType
    {
        AggregateType(const QString& _name = QString()) : id(0), name(_name) {}

        unsigned int id;
        QString name;

        bool insertInDatabase();
    };

    struct Car
    {
        Car(const QString& _name = QString()) : id(0), name(_name) {}

        unsigned int id;
        QString name;

        bool insertInDatabase();
    };

    struct Aggregate
    {
        Aggregate() : id(0) {}

        unsigned int id;
        QString number;
        QString name;
        AggregateType type;
        Car car;

        bool insertInDatabase();
    };
}

#endif // DATASTRUCTS_H
