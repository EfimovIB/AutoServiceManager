#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

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

    m_ui->invoiceNumber->setText("Num nacl");

    QSharedPointer<InvoiceSpare> s(new InvoiceSpare);

    s->invoice = m_invoice;
    s->spare.barcode = "1111";
    s->spare.name = "N1";
    s->spare.manufacturer.name = "Proiz1";
    s->price = 1.1;
    s->count = 1;

    m_spares << s;

    s = QSharedPointer<InvoiceSpare>(new InvoiceSpare);

    s->invoice = m_invoice;
    s->spare.barcode = "2222";
    s->spare.name = "N2";
    s->spare.manufacturer.name = "Proiz2";
    s->price = 2.2;
    s->count = 2;

    m_spares << s;

    s = QSharedPointer<InvoiceSpare>(new InvoiceSpare);

    s->invoice = m_invoice;
    s->spare.barcode = "3333";
    s->spare.name = "N3";
    s->spare.manufacturer.name = "Proiz3";
    s->price = 3.3;
    s->count = 3;

    m_spares << s;

    updateTreeView();
    //----------------
}

ContentWidgetInvoiceCreator::~ContentWidgetInvoiceCreator()
{
    delete m_ui;
}

void ContentWidgetInvoiceCreator::topButtonclicked()
{
    if (addedInvoiceCorrect() == false)
        return;

    m_invoice->number = m_ui->invoiceNumber->text();

    if (insertDataInDatabase())
    {
        clearForm();

        emit created();

        bottomButtonclicked();
    }
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

bool ContentWidgetInvoiceCreator::addedInvoiceCorrect() const
{
    return m_ui->invoiceNumber->text().isEmpty() == false;
}

bool ContentWidgetInvoiceCreator::insertDataInDatabase()
{
    QSqlDatabase::database().transaction();

    foreach ( QSharedPointer<InvoiceSpare> s, m_spares)
        if (s->insertInDatabase() == false)
            return false;

    QSqlDatabase::database().commit();

    return true;
}

void ContentWidgetInvoiceCreator::clearForm()
{
    m_spares.clear();
    m_invoice.clear();
    m_ui->invoiceNumber->clear();
    m_ui->dateEdit->setDate(QDate::currentDate());
    updateTreeView();
    clearFields();
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
