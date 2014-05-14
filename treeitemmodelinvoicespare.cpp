#include "treeitemmodelinvoicespare.h"
#include "datastructs.h"

namespace asmt
{

TreeItemModelInvoiceSpare::TreeItemModelInvoiceSpare(const QList<QSharedPointer<InvoiceSpare> >& _list, QObject* _parent)
  : QAbstractItemModel(_parent)
    , m_list(_list)
{}

int TreeItemModelInvoiceSpare::columnCount(const QModelIndex& parent) const
{
    return 5;
}

QVariant TreeItemModelInvoiceSpare::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
         return QVariant();

     if (role != Qt::DisplayRole)
         return QVariant();

     QSharedPointer<InvoiceSpare> s = m_list[index.internalId()];

     if (!s)
         return QVariant();

     switch (index.column())
     {
        case 0: return s->spare.barcode;
        case 1: return s->spare.name;
        case 2: return s->spare.manufacturer.name;
        case 3: return s->price;
        case 4: return s->count;
     }

     return QVariant();
}

QModelIndex TreeItemModelInvoiceSpare::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (parent.isValid())
        return QModelIndex();

    return createIndex(row, column, row);
}

QModelIndex TreeItemModelInvoiceSpare::parent(const QModelIndex& index) const
{
    return QModelIndex();
}

int TreeItemModelInvoiceSpare::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return m_list.size();
}

}
