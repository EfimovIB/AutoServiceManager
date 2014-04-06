#ifndef ASM_WAREHOUSETABLEDELEGATE_H
#define ASM_WAREHOUSETABLEDELEGATE_H

#include <QItemDelegate>

namespace asmt
{
    class WarehouseTableDelegate : public QItemDelegate
    {
    public:
        WarehouseTableDelegate(QObject* _parent = 0);

        QWidget* createEditor(QWidget* _parent, const QStyleOptionViewItem& _option, const QModelIndex& _index) const;
        void setEditorData(QWidget* _editor, const QModelIndex& _index) const;
        void setModelData(QWidget* _editor, QAbstractItemModel* _model, const QModelIndex& _index) const;
        void updateEditorGeometry(QWidget* _editor, const QStyleOptionViewItem& _option, const QModelIndex& _index) const;
    };
}

#endif //ASM_WAREHOUSETABLEDELEGATE_H
