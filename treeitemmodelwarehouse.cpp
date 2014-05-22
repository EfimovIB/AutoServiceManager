#include "treeitemmodelwarehouse.h"
#include "datastructs.h"

namespace asmt
{

TreeItemModelWareHouse::TreeItemModelWareHouse(QObject* _parent)
  : QAbstractItemModel(_parent)
{
    m_list = Spare::spares();
}

int TreeItemModelWareHouse::columnCount(const QModelIndex& parent) const
{
    return 4;
}

QVariant TreeItemModelWareHouse::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
         return QVariant();

     if (role != Qt::DisplayRole)
         return QVariant();

     QSharedPointer<Spare> s = m_list[index.internalId()];

     if (!s)
         return QVariant();

     switch (index.column())
     {
        case 0: return s->barcode;
        case 1: return s->name;
        case 2: return s->manufacturer.name;
        case 3: return s->count;
     }

     return QVariant();
}

QModelIndex TreeItemModelWareHouse::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (parent.isValid())
        return QModelIndex();

    return createIndex(row, column, row);
}

QModelIndex TreeItemModelWareHouse::parent(const QModelIndex& index) const
{
     return QModelIndex();
}

int TreeItemModelWareHouse::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return m_list.size();
}

}
