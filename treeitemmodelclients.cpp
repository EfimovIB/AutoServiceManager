#include <QDebug>

#include "treeitemmodelclients.h"
#include "datastructs.h"

namespace asmt
{

TreeItemModelClients::TreeItemModelClients(QObject *_parent)
  : QAbstractItemModel(_parent)
{
    m_map = Person::persons();
}

int TreeItemModelClients::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant TreeItemModelClients::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
         return QVariant();

     if (role != Qt::DisplayRole)
         return QVariant();

     QSharedPointer<Person> p = m_map[index.internalId()];

     if (!p)
         return QVariant();

     switch (index.column())
     {
        case 0: return p->name;
        case 1: return p->surname;
        case 2: return p->patronymic;
        case 3: return p->phone.first();
     }

     return QVariant();
}

QModelIndex TreeItemModelClients::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (parent.isValid())
        return QModelIndex();

    QMap<int, QSharedPointer<Person> >::iterator i = m_map.begin() + row;

    return createIndex(row, column, i.value()->id);
}

QModelIndex TreeItemModelClients::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int TreeItemModelClients::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_map.size();
}

}
