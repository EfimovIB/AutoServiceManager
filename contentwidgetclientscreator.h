#ifndef CONTENTWIDGETCLIENTSCREATOR_H
#define CONTENTWIDGETCLIENTSCREATOR_H

#include "contentwidget.h"

namespace Ui
{
class ContentWidgetClientsCreator;
}

namespace asmt
{
class ContentWidgetClientsCreator : public ContentWidget
{
    Q_OBJECT

public:
    explicit ContentWidgetClientsCreator(MainWidget* _mainWidget);
    explicit ContentWidgetClientsCreator(ContentWidget* _contentWidget);
    ~ContentWidgetClientsCreator();

    void topButtonclicked(){}
    void bottomButtonclicked() { switchOnPrev(); }

    QIcon topButtonIcon() { return QIcon(":/button/pictures/new.png"); }
    QIcon bottomButtonIcon() { return QIcon(":/button/pictures/home.png"); }

private:
    Ui::ContentWidgetClientsCreator* m_ui;
};
}

#endif // CONTENTWIDGETCLIENTSCREATOR_H
