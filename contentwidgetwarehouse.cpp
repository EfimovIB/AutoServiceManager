#include "contentwidgetwarehouse.h"
#include "ui_ContentWidgetWareHouse.h"
#include "contentwidgetinvoicecreator.h"
#include "treeitemmodelwarehouse.h"

namespace asmt
{

ContentWidgetWareHouse::ContentWidgetWareHouse(MainWidget* _mainWidget)
  : ContentWidget(_mainWidget)
  , m_ui(new Ui::ContentWidgetWareHouse)
  , m_creatInvoice(NULL)
{
    m_ui->setupUi(this);

    updateTreeView();
}

ContentWidgetWareHouse::ContentWidgetWareHouse(ContentWidget *_contentWidget)
  : ContentWidget(_contentWidget)
  , m_ui(new Ui::ContentWidgetWareHouse)
  , m_creatInvoice(NULL)
{
    m_ui->setupUi(this);

    updateTreeView();
}

ContentWidgetWareHouse::~ContentWidgetWareHouse()
{
    delete m_ui;
}

void ContentWidgetWareHouse::topButtonclicked()
{
    if (!m_creatInvoice)
    {
        m_creatInvoice = new ContentWidgetInvoiceCreator(this);

        connect(m_creatInvoice, SIGNAL(created()), SLOT(updateTreeView()));
    }

    switchOn(m_creatInvoice);
}

void ContentWidgetWareHouse::updateTreeView()
{
    m_ui->treeView->setModel(new TreeItemModelWareHouse);
}

}
