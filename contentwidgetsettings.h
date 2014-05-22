#ifndef CONTENTWIDGETSETTINGS_H
#define CONTENTWIDGETSETTINGS_H

#include "contentwidget.h"

namespace Ui
{
    class ContentWidgetSettings;
}

namespace asmt
{
class Connection;
class ContentWidgetSettings : public ContentWidget
{
    Q_OBJECT

public:
    explicit ContentWidgetSettings(MainWidget* _mainWidget);
    explicit ContentWidgetSettings(ContentWidget* _contentWidget);
    ~ContentWidgetSettings();

    void bottomButtonclicked() { switchOnPrev(); }

    QString bottomButtonText() { return tr("Домой"); }

    QIcon topButtonIcon() { return QIcon(); }
    QIcon bottomButtonIcon() { return QIcon(":/button/pictures/home.png"); }

private:

    void init();

private slots:

    void initDatabase() const;
    void dropDatabase() const;
    void recalcWareHouse() const;

    void connectStateChanged(bool);

    void hostChanged();
    void portChanged();
    void databaseChanged();
    void userChanged();
    void passwordChanged();

private:

    Ui::ContentWidgetSettings *m_ui;
    Connection* m_con;
};

}
#endif // CONTENTWIDGETSETTINGS_H
