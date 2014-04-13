#ifndef CONTENTWIDGETWAREHOUSE_H
#define CONTENTWIDGETWAREHOUSE_H

#include "contentwidget.h"

namespace Ui
{
    class ContentWidgetWareHouse;
}

namespace asmt
{

class ContentWidgetWareHouse : public ContentWidget
{
    Q_OBJECT

public:

    explicit ContentWidgetWareHouse(MainWidget* _mainWidget);
    explicit ContentWidgetWareHouse(ContentWidget* _contentWidget);
    ~ContentWidgetWareHouse();

    void bottomButtonclicked() { switchOnPrev(); }

    QIcon topButtonIcon() { return QIcon(":/button/pictures/new.png"); }
    QIcon bottomButtonIcon() { return QIcon(":/button/pictures/home.png"); }

private:

    Ui::ContentWidgetWareHouse *ui;
};

}

#endif // CONTENTWIDGETWAREHOUSE_H
