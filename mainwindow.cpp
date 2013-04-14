#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasemanager.h"

namespace asmt
{

	MainWindow::MainWindow()
		: QMainWindow(),
		m_ui( new Ui::MainWindow ),
		m_dm( new DatabaseManager)
	{
		m_ui->setupUi(this);

		m_dm->connect();
		if (m_dm->open() == false)
			qDebug() << m_dm->error();

		m_ui->goodsCount->setEnabled(false);

		connect(m_ui->btnCreateDatabase, SIGNAL(pressed()),           SLOT(initDatabase()));
		connect(m_ui->btnDropDatabase,   SIGNAL(pressed()),           SLOT(dropDatabase()));
		connect(m_ui->lBarcode,               SIGNAL(returnPressed ()),  SLOT(barcodeEntered()));
		connect(m_ui->goodsCount,           SIGNAL(editingFinished()), SLOT(addGoods()));

		updateGoodsList();
	}

	MainWindow::~MainWindow()
	{
		delete m_ui;
		delete m_dm;
	}

	void MainWindow::initDatabase() const
	{
		m_dm->initTables();
	}

	void MainWindow::dropDatabase() const
	{
		m_dm->dropTables();
	}

	void MainWindow::barcodeEntered() const
	{
		bool hasBarcode = m_ui->lBarcode->text().isEmpty()  == false;
		
		m_ui->goodsCount->setEnabled(hasBarcode);

		
		if (hasBarcode)
		{
			m_ui->goodsCount->setFocus();
			m_ui->goodsCount->selectAll();
		}
	}

	void MainWindow::addGoods()
	{
		QString barcode(m_ui->lBarcode->text());
		if (barcode.isEmpty())
			return;

		if (m_dm->exist(barcode) == false)
			m_dm->addGoods(barcode);
		
		m_dm->addGoods(barcode, m_ui->goodsCount->value());

		m_ui->goodsCount->blockSignals(true);

		m_ui->lBarcode->setFocus();
		m_ui->lBarcode->selectAll();
		m_ui->goodsCount->setEnabled(false);
		updateGoodsList();

		m_ui->goodsCount->blockSignals(false);
	}

	void MainWindow::updateGoodsList()
	{
		QList<Goods> list(m_dm->goods());
		m_ui->table->setRowCount(list.size());
		for (int i = 0; i < list.size(); ++i)
		{
			QString barcode = list[i].barcode();
			QString name = list[i].name();
			QString count = QString::number(list[i].count());

			m_ui->table->setItem(i, 0, new QTableWidgetItem(barcode));
			m_ui->table->setItem(i, 1, new QTableWidgetItem(name));
			m_ui->table->setItem(i, 2, new QTableWidgetItem(count));
		}
		int width = m_ui->table->contentsRect().width() / 3 - 1;
		m_ui->table->setColumnWidth(0, width);
		m_ui->table->setColumnWidth(1, width);
		m_ui->table->setColumnWidth(2, width);
	}

}