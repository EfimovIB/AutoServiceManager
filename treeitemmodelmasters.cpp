#include "treeitemmodelmasters.h"
#include "datastructs.h"

namespace asmt
{

TreeItemModelMasters::TreeItemModelMasters(QObject* _parent)
  : QAbstractItemModel(_parent)
{
    m_list = Master::masters();
}

int TreeItemModelMasters::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant TreeItemModelMasters::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
         return QVariant();

     if (role != Qt::DisplayRole)
         return QVariant();

     QSharedPointer<Master> m = master(index.internalId());

     if (!m)
         return QVariant();

     switch (index.column())
     {
        case 0: return m->person.name;
        case 1: return m->person.surname;
        case 2: return m->person.patronymic;
        case 3: return m->person.phone.first();
     }

     return QVariant();
}

QModelIndex TreeItemModelMasters::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (parent.isValid())
        return QModelIndex();

    return createIndex(row, column, m_list[row]->id);
}

QModelIndex TreeItemModelMasters::parent(const QModelIndex &index) const
{
     return QModelIndex();
}

int TreeItemModelMasters::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_list.size();
}

QSharedPointer<Master> TreeItemModelMasters::master(quint32 _id) const
{
    for (int i = 0; i < m_list.size(); i++)
    {
        if (m_list[i]->id == _id)
            return m_list[i];
    }

    return QSharedPointer<Master>(NULL);
}

}
