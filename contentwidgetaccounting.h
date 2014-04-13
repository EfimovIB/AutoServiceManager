#ifndef CONTENTWIDGETACCOUNTING_H
#define CONTENTWIDGETACCOUNTING_H

#include "contentwidget.h"

namespace Ui
{
    class ContentWidgetAccounting;
}
namespace asmt
{

class ContentWidgetAccounting : public ContentWidget
{
    Q_OBJECT

public:
    explicit ContentWidgetAccounting(MainWidget* _mainWidget);
    explicit ContentWidgetAccounting(ContentWidget* _prev);
    ~ContentWidgetAccounting();

    void bottomButtonclicked() { switchOnPrev(); }

    QIcon topButtonIcon() { return QIcon(":/button/pictures/new.png"); }
    QIcon bottomButtonIcon() { return QIcon(":/button/pictures/home.png"); }

private slots:

    void mastersClicked();
    void spareClicked();

private:

    Ui::ContentWidgetAccounting *m_ui;
};

}
#endif // CONTENTWIDGETACCOUNTING_H
