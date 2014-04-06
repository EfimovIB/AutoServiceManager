#include <QDebug>

#include "servicewidget.h"
#include "ui_ServiceWidget.h"

#include "service.h"
#include "person.h"

namespace asmt
{
static const int ProductColumn(0);
static const int StartDateColumn(1);
static const int EndDateColumn(2);
static const int OwnerColumn(3);

ServiceWidget::ServiceWidget()
  : QWidget()
  , m_ui(new Ui::ServiceWidget)
{
    m_ui->setupUi(this);
    fill();
}

ServiceWidget::~ServiceWidget()
{
    delete m_ui;
}

void ServiceWidget::updateForm()
{
    m_ui->table->clear();
    fill();
}

void ServiceWidget::fill()
{
    m_services = Service::servicesInProgress();

    m_ui->table->setRowCount(m_services.size());

    for (int i = 0; i < m_services.size(); ++i)
    {
        QString product;// = m_services[i]->name();
        QString stDate = m_services[i].startDateText();
        QString endDate = m_services[i].endDateText();
        QString owner = m_services[i].client()->fullName();

        m_ui->table->setItem(i, ProductColumn,    new QTableWidgetItem(product));
        m_ui->table->setItem(i, StartDateColumn,  new QTableWidgetItem(stDate));
        m_ui->table->setItem(i, EndDateColumn,    new QTableWidgetItem(endDate));
        m_ui->table->setItem(i, OwnerColumn,      new QTableWidgetItem(owner));
    }
}

}
