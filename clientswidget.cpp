#include "clientswidget.h"
#include "ui_clientswidget.h"

namespace asmt
{
	ClientsWidget::ClientsWidget()
		:QWidget(),
		m_ui(new Ui::ClientsWidget)
	{
		m_ui->setupUi(this);
	}

	ClientsWidget::~ClientsWidget()
	{
		delete m_ui;
	}
}