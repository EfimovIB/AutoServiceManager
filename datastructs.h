#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#include <QStringList>
#include <QDate>
#include <QSharedPointer>
#include <QPair>
#include <QMap>

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

        bool isValid() const;

        bool insertInDatabase();

        static QSharedPointer<Person> person(unsigned int _id);
        static QMap<int, QSharedPointer<Person> > persons();
        static QList<QSharedPointer<Person> > persons(const QString& _phone);
        static QStringList phones(unsigned int _idPerson);
    };

    struct Master
    {
        Master() : id(0), state(MasterState::Works) {}

        unsigned int id;
        Person person;
        MasterState state;
        QDate date;

        bool isValid() const;

        bool insertInDatabase();

        static QList<QSharedPointer<Master>> masters();
        static QSharedPointer<Master> master(unsigned int _id);
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
        static QSharedPointer<Aggregate> aggregate(unsigned int _id);
    };

    struct Service
    {
        Service() : id(0), state(S_Accepted), price(0), boxNumber(0) {}

        unsigned int id;
        Aggregate aggregate;
        Person person;
        Master master;
        ServiceState state;
        QDate startDate;
        QDate endDate;
        QString personComments;
        QString mastersComments;
        QString changed;
        int boxNumber;
        qreal price;

        bool insertInDatabase();

        static QSharedPointer<Service> service(unsigned int _id);
        static QList<QSharedPointer<Service> > service();
    };

    struct SimplifyService
    {
        SimplifyService() : id(0), state(S_Accepted), boxNumber(0) {}

        unsigned int id;
        QString aggregateName;
        QString personName;
        QString personPatronymic;
        ServiceState state;
        QDate startDate;
        QDate endDate;
        int boxNumber;

        static QList<QSharedPointer<SimplifyService> > service();
    };

    struct UsedSpares
    {
        UsedSpares() : id(0), spare(NULL), service(NULL) {}

        unsigned int id;
        QSharedPointer<Spare> spare;
        QSharedPointer<Service> service;

        bool insertInDatabase() { return false; } // todo
    };
}

#endif // DATASTRUCTS_H
