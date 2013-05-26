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
	int id() const;
	const QString& name() const;

	static Manufacturer* addManufacturer(const QString& _name);
	static const QList<Manufacturer*> manufacturers();
	static const Manufacturer const* manufacturer(int _id);
	static bool exist(int _id);

private:
	Manufacturer();
	static void checkListManufacturer();
	static void downloadListManufacturer();
	static int biggestExistId();
	void addInDatabase();
	
private:
	int m_id;
	QString m_name;
};
}

#endif //ASM_MANUFACTURER_H