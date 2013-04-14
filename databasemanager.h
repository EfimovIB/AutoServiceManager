#ifndef ASM_DATABASEMANAGER_H
#define ASM_DATABASEMANAGER_H

#include <QString>
#include <QList>
#include "goods.h"

namespace asmt
{
class DatabaseManager
{
public:
	DatabaseManager();

	void connect();
	bool open() const;
	QString error() const;

	void initTables() const;
	void dropTables() const;

	void addGoods(const QString& _barcode, const QString& _name = QString());
	void addGoods(const QString& _barcode, int _count);
	void refGoods(const QString& _barcode);
	void derefGoods(const QString& _barcode);
	bool exist(const QString& _barcode) const;
	QList<Goods> goods() const;

private:
	void dropTable( const QString& _name) const;

private:
	QString m_connectError;
};
}

#endif //ASM_DATABASEMANAGER_H