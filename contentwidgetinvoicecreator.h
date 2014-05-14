#ifndef CONTENTWIDGETINVOICECREATOR_H
#define CONTENTWIDGETINVOICECREATOR_H

#include <QList>
#include <QSharedPointer>

#include "contentwidget.h"

namespace Ui
{
    class ContentWidgetInvoiceCreator;
}

namespace asmt
{
struct InvoiceSpare;
struct Invoice;

class ContentWidgetInvoiceCreator : public ContentWidget
{
    Q_OBJECT

public:

    explicit ContentWidgetInvoiceCreator(MainWidget* _mainWidget);
    explicit ContentWidgetInvoiceCreator(ContentWidget* _contentWidget);
    ~ContentWidgetInvoiceCreator();

    void topButtonclicked();
    void bottomButtonclicked() { switchOnPrev(); }

    QIcon topButtonIcon() { return QIcon(":/button/pictures/accept.png"); }
    QIcon bottomButtonIcon() { return QIcon(":/button/pictures/reject.png"); }

private slots:

    void addInvoiceSpare();

private:

    void init();
    bool addedInvoiceSpareCorrect() const;

    void clearFields();
    void updateTreeView();

private:

    QList<QSharedPointer<InvoiceSpare> > m_spares;
    QSharedPointer<Invoice> m_invoice;
    Ui::ContentWidgetInvoiceCreator* m_ui;
};
}

#endif // CONTENTWIDGETINVOICECREATOR_H
