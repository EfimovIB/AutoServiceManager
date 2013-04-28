#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasemanager.h"
#include "warehousewidget.h"
#include "clientswidget.h"
#include "databasewidget.h"

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

	m_ui->tabWidget->addTab(warehouse, tr("�����"));
	m_ui->tabWidget->addTab(clients, tr("�������"));
	m_ui->tabWidget->addTab(databse, tr("���� ������"));
}

MainWindow::~MainWindow()
{
	delete m_ui;
}
}