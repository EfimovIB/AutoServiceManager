#ifndef TREEITEMMODELCLIENTS_H
#define TREEITEMMODELCLIENTS_H

#include <QAbstractItemModel>
#include <QMap>
#include <QSharedPointer>

namespace asmt
{
struct Person;

class TreeItemModelClients: public QAbstractItemModel
{
    Q_OBJECT

public:

    explicit TreeItemModelClients(QObject* _parent = 0);

    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex & index) const;
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

private:

    QSharedPointer<Person> master(quint32 _id) const;

private:

    QMap<int, QSharedPointer<Person> > m_map;
};

}

#endif // TREEITEMMODELCLIENTS_H
