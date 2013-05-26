#ifndef ASM_WAREHOUSEMODEL_H
#define ASM_WAREHOUSEMODEL_H

#include <QList>
#include <QAbstractListModel>

namespace asmt
{
class Goods;
class WarehouseModel : public QAbstractListModel
{
public:
	WarehouseModel();
	~WarehouseModel();

	QVariant data(const QModelIndex &index, int role) const;
	//QModelIndex	index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const = 0
	Qt::ItemFlags flags(const QModelIndex &index) const;
	int rowCount(const QModelIndex &parent) const;

private:
	QList<Goods*> m_list;
};

}

#endif //ASM_WAREHOUSEMODEL_H