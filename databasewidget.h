#ifndef ASM_DATABASEWIDGET_H
#define ASM_DATABASEWIDGET_H

#include <QWidget>

namespace Ui
{
    class DatabaseWidget;
}

namespace asmt
{
class Connection;
class DatabaseWidget : public QWidget
{
    Q_OBJECT
public:
    DatabaseWidget();
    ~DatabaseWidget();

private slots:
    void initDatabase() const;
    void dropDatabase() const;
    void connectStateChanged(bool);

private:
    Ui::DatabaseWidget* m_ui;
    Connection* m_con;
};
}

#endif //ASM_CLIENTSWIDGET_H
