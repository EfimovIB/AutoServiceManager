#include "warehousewidget.h"
#include "ui_WarehouseWidget.h"
#include "goods.h"

namespace asmt
{
	WarehouseWidget::WarehouseWidget()
		:QWidget(),
		m_ui(new Ui::WarehouseWidget),
		m_firstTime(true)
	{
		m_ui->setupUi(this);

		m_ui->goodsCount->setEnabled(false);

		m_goods = Goods::goods();

		connect(m_ui->lBarcode,   SIGNAL(returnPressed ()),  SLOT(barcodeEntered()));
		connect(m_ui->goodsCount, SIGNAL(editingFinished()), SLOT(addGoods()));
		connect(m_ui->table,      SIGNAL(itemChanged(QTableWidgetItem*)), SLOT(itemChanged(QTableWidgetItem*)));
	}

	WarehouseWidget::~WarehouseWidget()
	{
		delete m_ui;

		foreach(Goods* g, m_goods)
			delete g;
	}

	void WarehouseWidget::barcodeEntered() const
	{
		bool hasBarcode = m_ui->lBarcode->text().isEmpty()  == false;

		m_ui->goodsCount->setEnabled(hasBarcode);

		if (hasBarcode)
		{
			m_ui->goodsCount->setFocus();
			m_ui->goodsCount->selectAll();
		}
	}

	void WarehouseWidget::addGoods()
	{
		QString barcode(m_ui->lBarcode->text());
		if (barcode.isEmpty())
			return;

		int count(m_ui->goodsCount->value());
		if (Goods* g = goodsByBarcode(barcode))
			g->refCount(count);
		else
			m_goods << new Goods(barcode, count);
		
		m_ui->goodsCount->blockSignals(true);

		m_ui->lBarcode->setFocus();
		m_ui->lBarcode->selectAll();
		m_ui->goodsCount->setEnabled(false);
		
		updateGoodsList();

		m_ui->goodsCount->blockSignals(false);
	}

	void WarehouseWidget::updateGoodsList()
	{
		m_ui->table->setRowCount(m_goods.size());
		for (int i = 0; i < m_goods.size(); ++i)
		{
			QString barcode = m_goods[i]->barcode();
			QString name = m_goods[i]->name();
			QString count = QString::number(m_goods[i]->count());

			m_ui->table->setItem(i, 0, new QTableWidgetItem(barcode));
			m_ui->table->setItem(i, 1, new QTableWidgetItem(name));
			m_ui->table->setItem(i, 2, new QTableWidgetItem(count));
		}
	}

	void WarehouseWidget::showEvent(QShowEvent* _event)
	{
		QWidget::showEvent(_event);

		if (m_firstTime)
		{
			updateGoodsList();
			correctTableColumnWidth();
			m_firstTime = false;
		}
	}

	void WarehouseWidget::resizeEvent(QResizeEvent* _event)
	{
		QWidget::resizeEvent(_event);
		correctTableColumnWidth();
	}

	void WarehouseWidget::correctTableColumnWidth()
	{
		int width = m_ui->table->contentsRect().width() / m_ui->table->columnCount() - 1;

		for (int i = 0; i < m_ui->table->columnCount(); ++i)
			m_ui->table->setColumnWidth(i, width);
	}

	Goods* WarehouseWidget::goodsByBarcode(const QString& _code) const
	{
		for (int i = 0; i < m_goods.size(); ++i)
			if (m_goods[i]->barcode() == _code)
				return m_goods[i];

		return NULL;
	}

	void WarehouseWidget::itemChanged(QTableWidgetItem* _item)
	{
		if (_item->column() != 1)
			return;

		Goods* g = m_goods[_item->row()];
		g->setName( _item->text() );
	}

}