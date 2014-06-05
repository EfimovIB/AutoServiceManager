#include "treeitemmodelservice.h"
#include "datastructs.h"
#include "asmapi.h"

namespace asmt
{

TreeItemModelService::TreeItemModelService(QObject* _parent)
  : QAbstractItemModel(_parent)
{
    m_list = SimplifyService::service();
}

int TreeItemModelService::columnCount(const QModelIndex& parent) const
{
    return 7;
}

QVariant TreeItemModelService::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
         return QVariant();

     if (role != Qt::DisplayRole)
         return QVariant();

     QSharedPointer<SimplifyService> s = m_list[index.internalId()];

     if (!s)
         return QVariant();

     switch (index.column())
     {
        case 0: return s->aggregateName;
        case 1: return ServiceStateToStr(s->state);
        case 2: return s->boxNumber;
        case 3: return s->startDate;
        case 4: return s->personName;
        case 5: return s->personPatronymic;
        case 6: return s->endDate;
     }

     return QVariant();
}

QModelIndex TreeItemModelService::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (parent.isValid())
        return QModelIndex();

    return createIndex(row, column, row);
}

QModelIndex TreeItemModelService::parent(const QModelIndex& index) const
{
    return QModelIndex();
}

int TreeItemModelService::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return m_list.size();
}

QSharedPointer<SimplifyService> TreeItemModelService::simplifyService(int num) const
{
    return m_list[num];
}

}
