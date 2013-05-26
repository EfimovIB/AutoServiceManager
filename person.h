#ifndef ASM_CLIENT_H
#define ASM_CLIENT_H

#include <QList>
#include <QString>
#include <QStringList>

namespace asmt
{
class Person
{
public:
	enum Type
	{
		Client,
		Master
	};

	Person(const QString& _name, Type _type = Client);

	Type type() const;

	const QString& name() const;
	void setName(const QString& _name);
	const QString& surname() const;
	void setSurname(const QString& _surname);
	const QString& patronymic() const;
	void setPatronymic(const QString& _patronymic);

	QString fullName() const;

	const QStringList& phones() const;
	void setPhones(const QStringList& _phones);

	const QString& id() const;
	static QList<Person*> persons(Type _type);
	static Person* person(const QString& _id);

private:
	Person();
	static void dowloadClients();
	static void checkListClients();

	void addInDatabase();
	void updateNameInDatabase();
	void updateSurnameInDatabase();
	void updatePatronymicInDatabase();
	void updatePhonesInDatabase();

private:
	Type m_type;

	QString m_id;
	QString m_name;
	QString m_surname;
	QString m_patronymic;
	QStringList m_phones;
};
}

#endif //ASM_CLIENT_H