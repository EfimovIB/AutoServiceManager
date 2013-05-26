#ifndef ASM_WAREHOUSEWIDGET_H
#define ASM_WAREHOUSEWIDGET_H

#include <QWidget>
#include <QList>

class QTableWidgetItem;

namespace Ui
{
	class WarehouseWidget;
}

namespace asmt
{
class Goods;
class WarehouseWidget : public QWidget
{
	Q_OBJECT
public:
	WarehouseWidget();
	~WarehouseWidget();

private slots:
	void barcodeEntered() const;
	void addGoods();
	void itemChanged(QTableWidgetItem* _item);
	void cellDoubleClicked(int _row, int _column);

private:
	void updateGoodsList();
	void correctTableColumnWidth();

	void showEvent(QShowEvent* _event);
	void resizeEvent(QResizeEvent* _event);

	Goods* goodsByBarcode(const QString& _code) const;

private:
	Ui::WarehouseWidget* m_ui;
	bool m_firstTime;
	QList<Goods*> m_goods;
};
}

#endif //ASM_CLIENTSWIDGET_H
