#ifndef CONTENTWIDGETSERVICE_H
#define CONTENTWIDGETSERVICE_H

#include "contentwidget.h"

namespace Ui
{
    class ContentWidgetService;
}

namespace asmt
{
class ContentWidgetServiceCreator;

class ContentWidgetService : public ContentWidget
{
    Q_OBJECT

public:
    explicit ContentWidgetService(MainWidget* _mainWidget);
    explicit ContentWidgetService(ContentWidget* _contentWidget);

    ~ContentWidgetService();

    void topButtonclicked();
    void bottomButtonclicked() { switchOnPrev(); }

    QIcon topButtonIcon() { return QIcon(":/button/pictures/new.png"); }
    QIcon bottomButtonIcon() { return QIcon(":/button/pictures/home.png"); }

private slots:

    void updateTreeView();

private:
    Ui::ContentWidgetService *ui;
    ContentWidgetServiceCreator* m_creatInvoice;
};

}
#endif // CONTENTWIDGETSERVICE_H
