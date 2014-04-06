#ifndef ASM_ASMAPI_H
#define ASM_ASMAPI_H
#include <QString>

namespace asmt
{
    static const QString WarehouseTableName("warehouse");
    static const QString ManufacturerTableName("manufacturer");
    static const QString PersonTableName("Person");
    static const QString ServiceTableName("Service");
    static const QString AggregateTableName("Aggregate");
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
