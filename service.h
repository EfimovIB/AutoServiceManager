#ifndef ASM_SERVICE_H
#define ASM_SERVICE_H

#include <QDate>

namespace asmt
{
class Person;
class Service
{
public:
	Service(const Person const* _client);
		
	const QString& id() const;
	const QString& masterComments() const;
	const QString& clientComments() const;
	void setClientComments(const QString& _comment);
	const Person const* client() const;
	const Person const* master() const;
	void setMaster(const Person const* _master);
	const QDate& startDate() const;
	void setStartDate(const QDate& _date);
	QString startDateText() const;
	const QDate& endDate() const;
	QString endDateText() const;

	static QList<Service> services(const Person const* _client);
	static QList<Service> servicesInProgress();
	static QList<Service> servicesByStartDate(const QDate& _date);
	static QList<Service> servicesByEndDate(const QDate& _date);

private:
	Service();
	static QList<Service> listByTextQueryCondition(const QString& _text);

	void addInDatabase();
	void updateClientCommentsInDatabase();
	void updateStartDateInDatabase();
	void updateMasterInDatabase();

private:
	QString m_id;
	const Person const* m_client;
	const Person const* m_master;
	QString m_agregat;
	QString m_changed;
	QString m_masterComments;
	QString m_clientComments;
	double m_price;
	QDate m_startDate;
	QDate m_endDate;
};
}

#endif //ASM_SERVICE_H