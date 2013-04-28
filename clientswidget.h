#ifndef ASM_CLIENTSWIDGET_H
#define ASM_CLIENTSWIDGET_H

#include <QWidget>

namespace Ui
{
	class ClientsWidget;
}

namespace asmt
{
class ClientsWidget : public QWidget
{
public:
	ClientsWidget();
	~ClientsWidget();

private:
	Ui::ClientsWidget* m_ui;
};
}

#endif //ASM_CLIENTSWIDGET_H