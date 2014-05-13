#ifndef CONTENTWIDGETINVOICECREATOR_H
#define CONTENTWIDGETINVOICECREATOR_H

#include <QList>

#include "contentwidget.h"

namespace Ui
{
    class ContentWidgetInvoiceCreator;
}

namespace asmt
{
struct InvoiceSpare;

class ContentWidgetInvoiceCreator : public ContentWidget
{
    Q_OBJECT

public:

    explicit ContentWidgetInvoiceCreator(MainWidget* _mainWidget);
    explicit ContentWidgetInvoiceCreator(ContentWidget* _contentWidget);
    ~ContentWidgetInvoiceCreator();

    void bottomButtonclicked() { switchOnPrev(); }

    QIcon topButtonIcon() { return QIcon(":/button/pictures/accept.png"); }
    QIcon bottomButtonIcon() { return QIcon(":/button/pictures/reject.png"); }

private slots:

    void addInvoiceSpare();

private:

    QList<InvoiceSpare> m_spares;
    Ui::ContentWidgetInvoiceCreator* m_ui;
};
}

#endif // CONTENTWIDGETINVOICECREATOR_H
