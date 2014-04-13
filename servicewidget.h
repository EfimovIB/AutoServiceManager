#ifndef ASM_SERVICEWIDGET_H
#define ASM_SERVICEWIDGET_H

#include <QWidget>

namespace Ui
{
    class ServiceWidget;
}

namespace asmt
{
class Service;
class ServiceWidget : public QWidget
{
    Q_OBJECT
public:

    ServiceWidget();
    ~ServiceWidget();

public slots:

    void updateForm();

private slots:


private:

    void fill();

private:

    QList<Service> m_services;
    Ui::ServiceWidget* m_ui;
};
}

#endif //ASM_CLIENTSWIDGET_H
