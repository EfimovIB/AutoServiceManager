#ifndef TREEITEMMODELMASTERS_H
#define TREEITEMMODELMASTERS_H

#include <QAbstractItemModel>
#include <QList>
#include <QSharedPointer>

namespace asmt
{
struct Master;

class TreeItemModelMasters : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit TreeItemModelMasters(QObject* _parent = 0);

    int	columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex & index) const;
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

private:

    QSharedPointer<Master> master(quint32 _id) const;

private:

    QList<QSharedPointer<Master> > m_list; // todo QMap<int id, QSharedPointer<Master> > m_map;
};

}

#endif // TREEITEMMODELMASTERS_H
