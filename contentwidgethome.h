#ifndef CONTENTWIDGETHOME_H
#define CONTENTWIDGETHOME_H

#include <QWidget>
#include "contentwidget.h"
namespace Ui
{
    class ContentWidgetHome;
}
namespace asmt
{
class ContentWidgetService;
class ContentWidgetWareHouse;
class ContentWidgetSettings;
class ContentWidgetMasters;
class ContentWidgetHome : public ContentWidget
{
    Q_OBJECT

public:
    explicit ContentWidgetHome(MainWidget* _mainWidget);
    explicit ContentWidgetHome(ContentWidget* _contentWidget);
    ~ContentWidgetHome();

    QIcon topButtonIcon() { return QIcon(":/button/pictures/Exit.png"); }
    QIcon bottomButtonIcon() { return QIcon(":/button/pictures/lock.png"); }

private slots:

    void serviceClicked();
    void warehouseClicked();
    void settingsClicked();
    void mastersClicked();

private:

    Ui::ContentWidgetHome*   m_ui;
    ContentWidgetService*    m_service;
    ContentWidgetWareHouse*  m_warehouse;
    ContentWidgetSettings*   m_settings;
    ContentWidgetMasters*    m_masters;
};

}
#endif // CONTENTWIDGETHOME_H
