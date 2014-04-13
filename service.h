#ifndef ASM_SERVICE_H
#define ASM_SERVICE_H

#include <QDate>
#include "aggregate.h"

namespace asmt
{
class Person;
class Service
{
public:
    Service(const Person* _client);
    ~Service();

    const QString& id() const;
    const QString& masterComments() const;
    const QString& clientComments() const;
    void setClientComments(const QString& _comment);
    const Person* client() const;
    const Person* master() const;
    void setMaster(const Person* _master);
    const QDate& startDate() const;
    void setStartDate(const QDate& _date);
    QString startDateText() const;
    const QDate& endDate() const;
    QString endDateText() const;

    static QList<Service> services(const Person* _client);
    static QList<Service> servicesInProgress();
    static QList<Service> servicesByStartDate(const QDate& _date);
    static QList<Service> servicesByEndDate(const QDate& _date);

    Aggregate* aggregate() const;
    void setAggregate(Aggregate* _aggregate);

    int boxNumber() const;
    void setBoxNumber(int _boxNumber);

private:

    Service();
    static QList<Service> listByTextQueryCondition(const QString& _text);

    void addInDatabase();
    void updateClientCommentsInDatabase();
    void updateStartDateInDatabase();
    void updateMasterInDatabase();
    void updateAggregateInDatabase();
    void updateBoxNumberInDatabase();

private:

    QString m_id;
    const Person* m_client;
    const Person* m_master;
    Aggregate* m_aggregate;
    int m_boxNumber;
    QString m_changed;
    QString m_masterComments;
    QString m_clientComments;
    double m_price;
    QDate m_startDate;
    QDate m_endDate;
};
}

#endif //ASM_SERVICE_H
