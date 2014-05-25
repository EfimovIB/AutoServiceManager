#ifndef ASM_NEWSERVICEDIALOG_H
#define ASM_NEWSERVICEDIALOG_H

class QDate;
#include <QDialog>
#include <QList>

namespace Ui
{
    class NewServiceDialog;
}

namespace asmt
{
class Person_old;
class Service_old;
class Aggregate_old;
class NewServiceDialog : public QDialog
{
    Q_OBJECT
public:
    NewServiceDialog(QWidget* _parent = 0);
    ~NewServiceDialog();

    const QDate& date() const;
    Person_old* master() const;
    Aggregate_old* createAggregate() const;
    QString comment() const;
    int box() const;

    static Service_old* createNewService(Person_old* _client, QWidget* _parent = 0);

private:
    QList<Person_old*> m_masters;

private:
    Ui::NewServiceDialog* m_ui;
};
}

#endif //ASM_CLIENTSWIDGET_H
