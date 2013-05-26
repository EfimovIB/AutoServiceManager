#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "databasewidget.h"
#include "warehousewidget.h"
#include "clientswidget.h"
#include "servicewidget.h"

namespace asmt
{
MainWindow::MainWindow()
	: QMainWindow(),
	m_ui( new Ui::MainWindow )
{
	m_ui->setupUi(this);

	DatabaseWidget* databse = new DatabaseWidget;
	WarehouseWidget* warehouse = new WarehouseWidget;
	ClientsWidget* clients = new ClientsWidget;
	ServiceWidget* service = new ServiceWidget;

	m_ui->tabWidget->addTab(warehouse, tr("Склад"));
	m_ui->tabWidget->addTab(clients, tr("Клиенты"));
	m_ui->tabWidget->addTab(service, tr("Услуги"));
	m_ui->tabWidget->addTab(databse, tr("База данных"));
}

MainWindow::~MainWindow()
{
	delete m_ui;
}
}