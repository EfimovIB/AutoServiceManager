#ifndef ASM_SERVICE_H
#define ASM_SERVICE_H

#include <QDate>
#include "aggregate.h"

namespace asmt
{
class Person_old;
class Service_old
{
public:
    Service_old(const Person_old* _client);
    ~Service_old();

    const QString& id() const;
    const QString& masterComments() const;
    const QString& clientComments() const;
    void setClientComments(const QString& _comment);
    const Person_old* client() const;
    const Person_old* master() const;
    void setMaster(const Person_old* _master);
    const QDate& startDate() const;
    void setStartDate(const QDate& _date);
    QString startDateText() const;
    const QDate& endDate() const;
    QString endDateText() const;

    static QList<Service_old> services(const Person_old* _client);
    static QList<Service_old> servicesInProgress();
    static QList<Service_old> servicesByStartDate(const QDate& _date);
    static QList<Service_old> servicesByEndDate(const QDate& _date);

    Aggregate_old* aggregate() const;
    void setAggregate(Aggregate_old* _aggregate);

    int boxNumber() const;
    void setBoxNumber(int _boxNumber);

private:

    Service_old();
    static QList<Service_old> listByTextQueryCondition(const QString& _text);

    void addInDatabase();
    void updateClientCommentsInDatabase();
    void updateStartDateInDatabase();
    void updateMasterInDatabase();
    void updateAggregateInDatabase();
    void updateBoxNumberInDatabase();

private:

    QString m_id;
    const Person_old* m_client;
    const Person_old* m_master;
    Aggregate_old* m_aggregate;
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
