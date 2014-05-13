#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#include <QStringList>
#include <QDate>
#include <QSharedPointer>
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
        unsigned int id;
        QString number;
        QDate date;
    };

    struct Manufacturer
    {
        unsigned int id;
        QString name;
    };

    struct Spare
    {
        unsigned int id;
        Manufacturer  manufacturer;
        QString barcode;
        QString name;

        static QList<QSharedPointer<Spare>> spares(const QString& _barcode); // todo
    };

    struct InvoiceSpare
    {
        QSharedPointer<Invoice> invoice;
        Spare spare;
        qreal price;
        unsigned int count;
    };
}

#endif // DATASTRUCTS_H
