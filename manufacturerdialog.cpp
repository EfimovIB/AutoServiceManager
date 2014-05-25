#include "manufacturerdialog.h"
#include "ui_ManufacturerDialog.h"

#include "manufacturer.h"

namespace asmt
{
ManufacturerDialog::ManufacturerDialog(QWidget* _parent, Qt::WindowFlags _f)
  : QDialog(_parent, _f)
  , m_ui(new Ui::ManufacturerDialog)
{
    m_ui->setupUi(this);
    fillList();
    connect(m_ui->addButton,  SIGNAL(pressed()),                     SLOT(addManufacturer()));
    connect(m_ui->lineEdit,   SIGNAL(returnPressed()),               SLOT(addManufacturer()));
    connect(m_ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(itemClicked(QListWidgetItem*)));
}

ManufacturerDialog::~ManufacturerDialog()
{
    delete m_ui;
}

Manufacturer_old* ManufacturerDialog::getManufacturer(QWidget* _parent)
{
    ManufacturerDialog d(_parent);
    if (d.exec() == QDialog::Accepted)
        return d.choosedManufacturer();

    return NULL;
}

Manufacturer_old* ManufacturerDialog::choosedManufacturer() const
{
    int r = m_ui->listWidget->currentRow();
    return Manufacturer_old::manufacturers()[r];
}

void ManufacturerDialog::fillList()
{
    foreach(Manufacturer_old* m, Manufacturer_old::manufacturers())
        m_ui->listWidget->addItem(m->name());
}

void ManufacturerDialog::updateList()
{
    m_ui->listWidget->clear();
    fillList();
}

void ManufacturerDialog::addManufacturer()
{
    QString name = m_ui->lineEdit->text();

    if (name.isEmpty())
        return;

    m_ui->lineEdit->clear();

    Manufacturer_old::addManufacturer(name);

    updateList();
}

void ManufacturerDialog::itemClicked(QListWidgetItem* _item)
{
    if (NULL == _item)
        return;

    accept();
}

}
