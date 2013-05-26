#include <QDialog>
#include <QComboBox>

#include "warehousetabledelegate.h"
#include "manufacturer.h"
#include "warehouseapi.h"

namespace asmt
{
WarehouseTableDelegate::WarehouseTableDelegate(QObject* _parent)
	: QItemDelegate(_parent)
{}

QWidget* WarehouseTableDelegate::createEditor(QWidget* _parent, const QStyleOptionViewItem& _option, const QModelIndex& _index) const
 {
	 if (_index.column() == ManufacturerColumn)
	 {
		/*QComboBox* editor = new QComboBox(_parent);
		
		foreach(Manufacturer* m , Manufacturer::manufacturers())
			editor->addItem(m->name());

		editor->addItem("Не указан");
		editor->addItem("Новый");

		return editor;
		*/
		 return new QDialog(_parent);
	 }

	 return QItemDelegate::createEditor(_parent, _option, _index);
 }

 void WarehouseTableDelegate::setEditorData(QWidget* _editor, const QModelIndex& _index) const
 {
	 if (_index.column() == ManufacturerColumn)
	 {
	/* QString value = _index.model()->data(_index, Qt::EditRole).toString();

	 QComboBox* comboBox = static_cast<QComboBox*>(_editor);*/
	 //spinBox->setValue(value);
	 }

	 QItemDelegate::setEditorData(_editor, _index);
 }

 void WarehouseTableDelegate::setModelData(QWidget* _editor, QAbstractItemModel* _model, const QModelIndex& _index) const
 {
	 if (_index.column() == ManufacturerColumn)
	 {
		// QComboBox* comboBox = static_cast<QComboBox*>(_editor);
		// spinBox->interpretText();
		// int value = spinBox->value();

		 // model->setData(index, value, Qt::EditRole);
	 }

	 QItemDelegate::setModelData(_editor, _model, _index);
 }

 void WarehouseTableDelegate::updateEditorGeometry(QWidget* _editor, const QStyleOptionViewItem& _option, const QModelIndex& _index) const
 {
	 if (_index.column() == ManufacturerColumn)
	 {
	//	_editor->setGeometry(_option.rect);
	 }

	 QItemDelegate::updateEditorGeometry(_editor, _option, _index);
 }
}