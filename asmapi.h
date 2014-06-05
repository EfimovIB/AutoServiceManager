#ifndef ASM_ASMAPI_H
#define ASM_ASMAPI_H
#include <QString>
#include <QTextCodec>
#include <QObject>

namespace asmt
{
    static const QString PersonTableName("Person");
    static const QString PhoneTableName("Phones");
    static const QString MasterTableName("Masters");
    static const QString MasterStateTableName("MasterState");
    static const QString ManufacturerTableName("Manufacturer");
    static const QString SpareTableName("Spare");
    static const QString InvoiceTableName("Invoice");
    static const QString InvoiceSpareTableName("InvoiceSpare");
    static const QString AggregateTableName("Aggregate");
    static const QString AggregateTypeTableName("AggregateType");
    static const QString CarTableName("Car");
    static const QString ServiceStateTableName("ServiceState");
    static const QString ServiceTableName("Service");
    static const QString UsedSpareTableName("UsedSpare");
    static const QString WarehouseTableName("1");

    static const QString DbDateFormat("dd.MM.yyyy");

    enum MasterState
    {
        Works = 1,
        MasterStateCount
    };

    static QString MasterStateToStr(MasterState s)
    {
        switch (s)
        {
        case Works: return  QObject::tr("Работает");
        }

        return "";
    }

    enum ServiceState
    {
        S_Accepted    = 1,
        S_Progress    = 2,
        S_Done        = 3,
        S_Warrantying = 4,
        S_Given       = 5,
        ServiceStateCount
    };

    static QString ServiceStateToStr(ServiceState s)
    {
        switch (s)
        {
        case S_Accepted:    return QObject::tr("Принят");
        case S_Progress:    return QObject::tr("В работе");
        case S_Done:        return QObject::tr("Сделан");
        case S_Warrantying: return QObject::tr("Гарантийный ремонт");
        case S_Given:       return QObject::tr("Отдан");
        }

        return "";
    }
}
/*
to do
Добавить в отображение сервиса инфу об агрегате
Проверить запросы агрегата
Доделать выборки по сущности агрегат
    -> Проверять диалог нового заказа на пустые поля
Все формы наследуются от базовой с virtual void updateForm() = 0;
Переделать списки на Model & Delegate
    -> сделать фильтрацию моделей
Сделать ввод товара через номер наклодной
Сделать разграничение доступа пользователей
*/
#endif //ASM_ASMAPI_H
