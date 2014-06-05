#ifndef TREEITEMMODELSERVICE_H
#define TREEITEMMODELSERVICE_H

#include <QAbstractItemModel>
#include <QSharedPointer>

namespace asmt
{
struct SimplifyService;

class TreeItemModelService : public QAbstractItemModel
{
    Q_OBJECT

public:

    explicit TreeItemModelService(QObject* _parent = 0);

    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex& index) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;

    QSharedPointer<SimplifyService> simplifyService(int num) const;

private:

    QList<QSharedPointer<SimplifyService> > m_list;

};
}
#endif // TREEITEMMODELSERVICE_H
