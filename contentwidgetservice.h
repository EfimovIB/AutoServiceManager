#ifndef CONTENTWIDGETSERVICE_H
#define CONTENTWIDGETSERVICE_H

#include <QMap>

#include "contentwidget.h"

class QModelIndex;

namespace Ui
{
    class ContentWidgetService;
}

namespace asmt
{
struct Service;
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

private:

    void init();
    void fillDetails(unsigned int _id);

private slots:

    void updateTreeView();
    void currentChanged(const QModelIndex&, const QModelIndex&);
    void edit();
    void save();

    void agregateNameChanged();
    void agregateTypeChanged();
    void agregateNumberChanged();
    void carChanged();
    void boxNumberChanged();
    void changedChanged();//???
    void telephoneChanged();
    void surnameChanged();
    void nameChanged();
    void patronymicChanged();
    void personCommentsChanged();
    void startDateChanged();
    void endDateChanged();
    void mastersCommentsChanged();
    void priceChanged();

private:

    Ui::ContentWidgetService *m_ui;
    ContentWidgetServiceCreator* m_creatInvoice;
    TreeItemModelService* m_model;
    QSharedPointer<Service> m_service;
    QMap<QString, QString> m_changes;
};

}
#endif // CONTENTWIDGETSERVICE_H
