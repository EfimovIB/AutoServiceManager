#ifndef ASM_GOODS_H
#define ASM_GOODS_H

#include <QString>
#include <QObject>

namespace asmt
{
class Manufacturer;
class  Goods : QObject
{
    Q_OBJECT
public:
    Goods(const QString& _barcode, const QString& _name = QString(), int _count = 0);
    Goods(const QString& _barcode, int _count = 0);

    const QString& barcode() const;
    const QString& name() const;
    int count() const;
    const Manufacturer* manufacturer() const;
    QString manufacturerName() const;
    void setManufacturer(int _id);

    static QList<Goods*> goods();

public slots: 

    void setName(const QString& _name);


    void refCount(int _ref);

private:
    Goods();
    void addInDatabase();
    void updateNameInDatabase();
    void updateManufacturerInDatabase();
    QString manufacturerValueToDatabase() const;

private:
    QString m_barcode;
    QString m_name;
    const Manufacturer* m_manufacturer;
    int m_count;
};
}

#endif //ASM_GOODS_H
