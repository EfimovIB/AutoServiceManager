#ifndef ASM_CLIENTSWIDGET_H
#define ASM_CLIENTSWIDGET_H

#include <QWidget>
#include <QList>

namespace Ui
{
	class ClientsWidget;
}

class QTableWidgetItem;

namespace asmt
{
class Person;
class ClientsWidget : public QWidget
{
	Q_OBJECT
public:
	ClientsWidget();
	~ClientsWidget();

protected:
	void showEvent(QShowEvent* _event);
	void resizeEvent(QResizeEvent* _event);

protected slots:
	void addClient();
	void itemChanged(QTableWidgetItem* _item);
	void addService();

private:
	void updateClientsList();
	void correctTableColumnWidth();
private:
	Ui::ClientsWidget* m_ui;
	bool m_firstTime;
	QList<Person*> m_clients;
};
}

#endif //ASM_CLIENTSWIDGET_H