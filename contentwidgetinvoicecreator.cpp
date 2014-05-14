#include "contentwidgetinvoicecreator.h"
#include "ui_ContentWidgetInvoiceCreator.h"
#include "datastructs.h"
#include "treeitemmodelinvoicespare.h"

namespace asmt
{
ContentWidgetInvoiceCreator::ContentWidgetInvoiceCreator(MainWidget* _mainWidget)
  : ContentWidget(_mainWidget)
  , m_ui(new Ui::ContentWidgetInvoiceCreator)
  , m_invoice(new Invoice)
{
    init();
}

ContentWidgetInvoiceCreator::ContentWidgetInvoiceCreator(ContentWidget* _contentWidget)
  : ContentWidget(_contentWidget)
  , m_ui(new Ui::ContentWidgetInvoiceCreator)
  , m_invoice(new Invoice)
{
    init();
}

void ContentWidgetInvoiceCreator::init()
{
    m_ui->setupUi(this);

    connect(m_ui->add, SIGNAL(clicked()), SLOT(addInvoiceSpare()));
}

ContentWidgetInvoiceCreator::~ContentWidgetInvoiceCreator()
{
    delete m_ui;
}

void ContentWidgetInvoiceCreator::topButtonclicked()
{
    // todo firstly 1 check Invoice 2 add all at db
}

void ContentWidgetInvoiceCreator::addInvoiceSpare()
{
    if (addedInvoiceSpareCorrect() == false)
        return; // todo add label with text of error

    QSharedPointer<InvoiceSpare> s(new InvoiceSpare);

    s->invoice = m_invoice;
    s->spare.barcode = m_ui->barcode->text();
    s->spare.name = m_ui->name->text();
    s->spare.manufacturer.name = m_ui->manufacturer->text();
    s->price = m_ui->price->text().toFloat();
    s->count = m_ui->count->text().toUInt();

    m_spares << s;

    clearFields();
    updateTreeView();
}

bool ContentWidgetInvoiceCreator::addedInvoiceSpareCorrect() const
{
    // todo add check what field is - int? string? float?
    return m_ui->barcode->text().isEmpty() == false
        && m_ui->name->text().isEmpty() == false
        && m_ui->price->text().isEmpty() == false
            && m_ui->count->text().isEmpty() == false;
}

void ContentWidgetInvoiceCreator::clearFields()
{
    m_ui->barcode->clear();
    m_ui->name->clear();
    m_ui->manufacturer->clear();
    m_ui->price->clear();
    m_ui->count->clear();
}

void ContentWidgetInvoiceCreator::updateTreeView()
{
    m_ui->treeView->setModel(new TreeItemModelInvoiceSpare(m_spares));
}
}
