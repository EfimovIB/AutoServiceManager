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

    struct AgregateType
    {
        AgregateType(const QString& _name = QString()) : id(0), name(_name) {}

        unsigned int id;
        QString name;
    };

    struct Car
    {
        Car(const QString& _name = QString()) : id(0), name(_name) {}

        unsigned int id;
        QString name;
    };

    struct Agregate
    {
        Agregate() : id(0), number(0) {}

        unsigned int id;
        unsigned int number;
        QString name;
        AgregateType type;
        Car car;
    };
}

#endif // DATASTRUCTS_H
