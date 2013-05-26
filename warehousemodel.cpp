#include <QStringList>

#include "goods.h"
#include "warehousemodel.h"

namespace asmt
{
WarehouseModel::WarehouseModel()
	:QAbstractListModel()
{
	m_list = Goods::goods();
}

WarehouseModel::~WarehouseModel()
{
	for (int i = 0; i < m_list.size(); ++i)
		delete m_list[i];
}

QVariant WarehouseModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	return m_list[index.row()]->barcode();
	/*
	if (role == Qt::DecorationRole)
		return QIcon(pixmaps.value(index.row()).scaled(m_PieceSize, m_PieceSize,
		Qt::KeepAspectRatio, Qt::SmoothTransformation));
	else if (role == Qt::UserRole)
		return pixmaps.value(index.row());
	else if (role == Qt::UserRole + 1)
		return locations.value(index.row());
	*/
	return QVariant();
}

Qt::ItemFlags WarehouseModel::flags(const QModelIndex &index) const
{
	if (index.isValid())
		return (Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);

	return Qt::ItemIsDropEnabled;
}


int WarehouseModel::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	
	return m_list.size();
}

}