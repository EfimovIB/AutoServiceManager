#ifndef ASM_MANUFACTURER_H
#define ASM_MANUFACTURER_H
#include <QString>
#include <QList>
#include <QObject>

namespace asmt
{
class Manufacturer : public QObject
{
	Q_OBJECT
public:
	Manufacturer(const QString& _name);

	const QString& name() const;

	static QList<Manufacturer*> manufacturer();

public slots:
	void setName(const QString& _name);

private:
	int m_id;
	QString m_name;
};
}

#endif //ASM_MANUFACTURER_H