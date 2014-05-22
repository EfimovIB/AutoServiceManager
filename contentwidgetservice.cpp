#include "contentwidgetservice.h"
#include "ui_ContentWidgetService.h"
#include "contentwidgetservicecreator.h"

namespace asmt
{
ContentWidgetService::ContentWidgetService(MainWidget* _mainWidget)
  : ContentWidget(_mainWidget)
  , ui(new Ui::ContentWidgetService)
  , m_creatInvoice(NULL)
{
    ui->setupUi(this);
}

ContentWidgetService::ContentWidgetService(ContentWidget* _contentWidget)
  : ContentWidget(_contentWidget)
  , ui(new Ui::ContentWidgetService)
  , m_creatInvoice(NULL)
{
    ui->setupUi(this);
}

ContentWidgetService::~ContentWidgetService()
{
    delete ui;
}

void ContentWidgetService::topButtonclicked()
{
    if (!m_creatInvoice)
    {
        m_creatInvoice = new ContentWidgetServiceCreator(this);

        connect(m_creatInvoice, SIGNAL(created()), SLOT(updateTreeView()));
    }

    switchOn(m_creatInvoice);
}

void ContentWidgetService::updateTreeView()
{
    // todo add update
}
}
