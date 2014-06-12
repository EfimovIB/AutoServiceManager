#ifndef ASM_DATABASEMANAGER_H
#define ASM_DATABASEMANAGER_H

class QString;

namespace asmt
{
class DatabaseManager
{
public:

    static void initTables();
    static void dropTables();
    static bool recalcSpareCount();
    static bool execQuery(const QString& _text);

private:
    static void dropTable(const QString& _name);
    static void execInitTable(const QString& _text);
};
}

#endif //ASM_DATABASEMANAGER_H
