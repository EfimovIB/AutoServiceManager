#ifndef CONTENTWIDGETMASTERS_H
#define CONTENTWIDGETMASTERS_H

#include "contentwidget.h"

namespace Ui
{
    class ContentWidgetMasters;
}

namespace asmt
{
class ContentWidgetMastersCreator;
class ContentWidgetMasters : public ContentWidget
{
    Q_OBJECT

public:
    explicit ContentWidgetMasters(MainWidget* _mainWidget);
    explicit ContentWidgetMasters(ContentWidget* _prev);
    ~ContentWidgetMasters();

    void topButtonclicked();
    void bottomButtonclicked() { switchOnPrev(); }

    QIcon topButtonIcon() { return QIcon(":/button/pictures/new.png"); }
    QIcon bottomButtonIcon() { return QIcon(":/button/pictures/home.png"); }

public slots:

    void updateList();

private:

    void init();

private:

    Ui::ContentWidgetMasters* m_ui;
    ContentWidgetMastersCreator* m_creator;
};

}
#endif // CONTENTWIDGETMASTERS_H
