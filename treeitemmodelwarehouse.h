#ifndef TREEITEMMODELWAREHOUSE_H
#define TREEITEMMODELWAREHOUSE_H

#include <QAbstractItemModel>
#include <QList>
#include <QPair>
#include <QSharedPointer>

namespace asmt
{
struct Spare;

class TreeItemModelWareHouse : public QAbstractItemModel
{
    Q_OBJECT

public:

    explicit TreeItemModelWareHouse(QObject* _parent = 0);

    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex & index) const;
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

private:

    QList<QSharedPointer<Spare> > m_list;
};

}

#endif // TREEITEMMODELWAREHOUSE_H
