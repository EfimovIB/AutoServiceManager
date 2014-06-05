#ifndef CONTENTWIDGETSERVICECREATOR_H
#define CONTENTWIDGETSERVICECREATOR_H

#include "contentwidget.h"

namespace Ui
{
    class ContentWidgetServiceCreator;
}

namespace asmt
{
class ContentWidgetServiceCreator : public ContentWidget
{
    Q_OBJECT

public:

    explicit ContentWidgetServiceCreator(MainWidget* _mainWidget);
    explicit ContentWidgetServiceCreator(ContentWidget* _contentWidget);
    ~ContentWidgetServiceCreator();

    void topButtonclicked();
    void bottomButtonclicked() { switchOnPrev(); }

    QIcon topButtonIcon() { return QIcon(":/button/pictures/new.png"); }
    QIcon bottomButtonIcon() { return QIcon(":/button/pictures/home.png"); }

signals:

    void created();

private:

    void clearForm();

private:

    Ui::ContentWidgetServiceCreator* m_ui;
};
}

#endif // CONTENTWIDGETSERVICECREATOR_H
