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

    void hostChanged();
    void portChanged();
    void databaseChanged();
    void userChanged();
    void passwordChanged();

private:

    Ui::DatabaseWidget* m_ui;
    Connection* m_con;
};
}

#endif //ASM_CLIENTSWIDGET_H
