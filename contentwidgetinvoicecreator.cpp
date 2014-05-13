#include "contentwidgetinvoicecreator.h"
#include "ui_ContentWidgetInvoiceCreator.h"
#include "datastructs.h"

namespace asmt
{
ContentWidgetInvoiceCreator::ContentWidgetInvoiceCreator(MainWidget* _mainWidget)
  : ContentWidget(_mainWidget)
  , m_ui(new Ui::ContentWidgetInvoiceCreator)
{
    m_ui->setupUi(this);

    connect(m_ui->add, SIGNAL(clicked()), SLOT(addInvoiceSpare()));
}

ContentWidgetInvoiceCreator::ContentWidgetInvoiceCreator(ContentWidget* _contentWidget)
  : ContentWidget(_contentWidget)
  , m_ui(new Ui::ContentWidgetInvoiceCreator)
{
    m_ui->setupUi(this);
}

ContentWidgetInvoiceCreator::~ContentWidgetInvoiceCreator()
{
    delete m_ui;
}

void ContentWidgetInvoiceCreator::addInvoiceSpare()
{
    // todo firstly
    m_spares << InvoiceSpare();
}
}
