#ifndef CONTENTWIDGETSERVICE_H
#define CONTENTWIDGETSERVICE_H

#include "contentwidget.h"

namespace Ui
{
    class ContentWidgetService;
}

namespace asmt
{

class ContentWidgetService : public ContentWidget
{
    Q_OBJECT

public:
    explicit ContentWidgetService(MainWidget* _mainWidget);
    explicit ContentWidgetService(ContentWidget* _contentWidget);

    ~ContentWidgetService();

    void bottomButtonclicked() { switchOnPrev(); }

    QIcon topButtonIcon() { return QIcon(":/button/pictures/new.png"); }
    QIcon bottomButtonIcon() { return QIcon(":/button/pictures/home.png"); }

private:
    Ui::ContentWidgetService *ui;
};

}
#endif // CONTENTWIDGETSERVICE_H
