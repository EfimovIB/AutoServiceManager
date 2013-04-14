#ifndef ASM_MAINWINDOW_H
#define ASM_MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
	class MainWindow;
}

namespace asmt
{
	class DatabaseManager;
	class MainWindow : public QMainWindow
	{
		Q_OBJECT
	public:
		MainWindow();
		~MainWindow();

	private slots:
		void initDatabase() const;
		void dropDatabase() const;
		void barcodeEntered() const;
		void addGoods();
		void updateGoodsList();

	private:
		Ui::MainWindow* m_ui;
		DatabaseManager* m_dm;
	};
}

#endif //ASM_MAINWINDOW_H