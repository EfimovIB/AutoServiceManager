#include "contentwidgetwarehouse.h"
#include "ui_ContentWidgetWareHouse.h"
#include "contentwidgetinvoicecreator.h"

namespace asmt
{

ContentWidgetWareHouse::ContentWidgetWareHouse(MainWidget* _mainWidget)
  : ContentWidget(_mainWidget)
  , ui(new Ui::ContentWidgetWareHouse)
  , m_creatInvoice(NULL)
{
    ui->setupUi(this);
}

ContentWidgetWareHouse::ContentWidgetWareHouse(ContentWidget *_contentWidget)
  : ContentWidget(_contentWidget)
  , ui(new Ui::ContentWidgetWareHouse)
  , m_creatInvoice(NULL)
{
    ui->setupUi(this);
}

ContentWidgetWareHouse::~ContentWidgetWareHouse()
{
    delete ui;
}

void ContentWidgetWareHouse::topButtonclicked()
{
    if (!m_creatInvoice)
    {
        m_creatInvoice = new ContentWidgetInvoiceCreator(this);
//        connect(m_creatInvoice, SIGNAL(created()), SLOT(updateList()));
    }

    switchOn(m_creatInvoice);
}

}
