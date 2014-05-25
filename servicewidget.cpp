#include <QDebug>

#include "servicewidget.h"
#include "ui_ServiceWidget.h"

#include "service.h"
#include "person.h"

namespace asmt
{
static const int IdColumn(0);
//static const int ProductColumn(1);
//static const int StartDateColumn(2);
//static const int EndDateColumn(3);
static const int OwnerColumn(1);

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
    m_services = Service_old::servicesInProgress();

    m_ui->table->setRowCount(m_services.size());

    for (int i = 0; i < m_services.size(); ++i)
    {
        QString id = m_services[i].id();
//        QString product = m_services[i].name();
        QString stDate = m_services[i].startDateText();
        QString endDate = m_services[i].endDateText();
        QString owner = m_services[i].client()->fullName();

        m_ui->table->setItem(i, IdColumn,         new QTableWidgetItem(id ));
//        m_ui->table->setItem(i, ProductColumn,    new QTableWidgetItem(product));
//        m_ui->table->setItem(i, StartDateColumn,  new QTableWidgetItem(stDate));
//        m_ui->table->setItem(i, EndDateColumn,    new QTableWidgetItem(endDate));
        m_ui->table->setItem(i, OwnerColumn,      new QTableWidgetItem(owner));
    }
}

}
