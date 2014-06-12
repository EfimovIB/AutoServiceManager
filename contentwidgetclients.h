#ifndef CONTENTWIDGETCLIENTS_H
#define CONTENTWIDGETCLIENTS_H

#include "contentwidget.h"

namespace Ui
{
class ContentWidgetClients;
}

namespace asmt
{
class ContentWidgetClientsCreator;

class ContentWidgetClients : public ContentWidget
{
    Q_OBJECT

public:
    explicit ContentWidgetClients(MainWidget* _mainWidget);
    explicit ContentWidgetClients(ContentWidget* _contentWidget);
    ~ContentWidgetClients();

    void topButtonclicked();
    void bottomButtonclicked() { switchOnPrev(); }

    QIcon topButtonIcon() { return QIcon(":/button/pictures/new.png"); }
    QIcon bottomButtonIcon() { return QIcon(":/button/pictures/home.png"); }

private:

    Ui::ContentWidgetClients* m_ui;
    ContentWidgetClientsCreator* m_creator;
};
}

#endif // CONTENTWIDGETCLIENTS_H
