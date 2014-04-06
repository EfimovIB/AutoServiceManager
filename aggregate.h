#ifndef ASM_AGGREGATE_H
#define ASM_AGGREGATE_H

#include <QString>

namespace asmt
{

class Aggregate
{
    Aggregate();
public:
    Aggregate(const QString& _name, const QString& _type, const QString& _car, const QString& _number);

    int id() const;
    void setId(int _id);

    QString name() const;
    void setName(const QString& _agregatName);

    QString type() const;
    void setType(const QString& _agregatType);

    QString car() const;
    void setCar(const QString& _car);

    QString number() const;
    void setNumber(const QString& _number);

    static Aggregate* aggregate(int _id);
private:

    void addInDatabase();
    int maxValue() const;

private:
    int m_id;
    QString m_name;
    QString m_type;
    QString m_car;
    QString m_number;
};

}
#endif // ASM_AGGREGATE_H
