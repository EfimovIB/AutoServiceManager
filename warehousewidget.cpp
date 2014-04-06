#include "warehousewidget.h"
#include "ui_WarehouseWidget.h"
#include "warehousemodel.h"
#include "goods.h"
#include "warehousetabledelegate.h"
#include "warehouseapi.h"
#include "manufacturerdialog.h"
#include "manufacturer.h"

namespace asmt
{
WarehouseWidget::WarehouseWidget()
  : QWidget()
  , m_ui(new Ui::WarehouseWidget)
  , m_firstTime(true)
{
    m_ui->setupUi(this);

    m_ui->goodsCount->setEnabled(false);

    m_goods = Goods::goods();

    connect(m_ui->lBarcode,   SIGNAL(returnPressed()),  SLOT(barcodeEntered()));
    connect(m_ui->goodsCount, SIGNAL(editingFinished()), SLOT(addGoods()));
    connect(m_ui->table,      SIGNAL(itemChanged(QTableWidgetItem*)), SLOT(itemChanged(QTableWidgetItem*)));
    connect(m_ui->table,      SIGNAL(cellDoubleClicked(int, int)), SLOT(cellDoubleClicked(int, int)));

    //m_ui->table->setItemDelegate(new WarehouseTableDelegate);
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
        QString manufact = m_goods[i]->manufacturerName();
        QString count = QString::number(m_goods[i]->count());

        m_ui->table->setItem(i, BarcodeColumn,      new QTableWidgetItem(barcode));
        m_ui->table->setItem(i, NameColumn,         new QTableWidgetItem(name));
        m_ui->table->setItem(i, ManufacturerColumn, new QTableWidgetItem(manufact));
        m_ui->table->setItem(i, CountColumn,        new QTableWidgetItem(count));
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
    int width = (m_ui->table->contentsRect().width() - 1)/ m_ui->table->columnCount();

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
    if (_item->column() != NameColumn)
        return;

    Goods* g = m_goods[_item->row()];

    if (_item->column() == NameColumn)
        g->setName( _item->text() );
    if (_item->column() == ManufacturerColumn)
        ;
}

void WarehouseWidget::cellDoubleClicked(int _row, int _column)
{
    if (_column == ManufacturerColumn)
        if (Manufacturer* m = ManufacturerDialog::getManufacturer(this))
        {
            Goods* g = m_goods[_row];
            g->setManufacturer(m->id());
            updateGoodsList();
        }

}

}
