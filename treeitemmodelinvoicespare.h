#ifndef TREEITEMMODELINVOICESPARE_H
#define TREEITEMMODELINVOICESPARE_H

#include <QAbstractItemModel>
#include <QSharedPointer>
#include <QList>

namespace asmt
{

struct InvoiceSpare;

class TreeItemModelInvoiceSpare : public QAbstractItemModel
{
    Q_OBJECT

public:

    explicit TreeItemModelInvoiceSpare(const QList<QSharedPointer<InvoiceSpare> >& _list, QObject* _parent = 0);

    int	columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex & index) const;
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

private:

    QList<QSharedPointer<InvoiceSpare> > m_list;

};

}

#endif // TREEITEMMODELINVOICESPARE_H
