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
class Person;
class Service;
class Aggregate;
class NewServiceDialog : public QDialog
{
    Q_OBJECT
public:
    NewServiceDialog(QWidget* _parent = 0);
    ~NewServiceDialog();

    const QDate& date() const;
    Person* master() const;
    Aggregate* createAggregate() const;
    QString comment() const;
    int box() const;

    static Service* createNewService(Person* _client, QWidget* _parent = 0);
private:
    QList<Person*> m_masters;

private:
    Ui::NewServiceDialog* m_ui;
};
}

#endif //ASM_CLIENTSWIDGET_H
