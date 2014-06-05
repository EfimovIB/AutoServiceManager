#ifndef CONTENTWIDGETSERVICE_H
#define CONTENTWIDGETSERVICE_H

#include "contentwidget.h"
class QModelIndex;

namespace Ui
{
    class ContentWidgetService;
}

namespace asmt
{
class ContentWidgetServiceCreator;
class TreeItemModelService;

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
    void currentChanged(const QModelIndex&, const QModelIndex&);

private:

    void fillDetails(unsigned int _id);

private:
    Ui::ContentWidgetService *m_ui;
    ContentWidgetServiceCreator* m_creatInvoice;
    TreeItemModelService* m_model;
};

}
#endif // CONTENTWIDGETSERVICE_H
