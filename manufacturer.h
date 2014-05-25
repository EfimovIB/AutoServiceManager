#ifndef ASM_MANUFACTURER_H
#define ASM_MANUFACTURER_H
#include <QString>
#include <QList>
#include <QObject>

namespace asmt
{
class Manufacturer_old : public QObject
{
    Q_OBJECT
public:
    int id() const;
    const QString& name() const;

    static Manufacturer_old* addManufacturer(const QString& _name);
    static const QList<Manufacturer_old*> manufacturers();
    static const Manufacturer_old* manufacturer(int _id);
    static bool exist(int _id);

private:
    Manufacturer_old();
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
