#ifndef ASM_ASMAPI_H
#define ASM_ASMAPI_H
#include <QString>

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
