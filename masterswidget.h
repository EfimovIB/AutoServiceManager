#ifndef MASTERSWIDGET_H
#define MASTERSWIDGET_H

#include <QWidget>
#include <QList>

namespace Ui
{
    class MastersWidget;
}

class QTableWidgetItem;

namespace asmt
{
class Person;

class MastersWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MastersWidget(QWidget *parent = 0);
    ~MastersWidget();
protected:
    void showEvent(QShowEvent* _event);
    void resizeEvent(QResizeEvent* _event);

private:
    void updateMastersList();
    void correctTableColumnWidth();

private slots:
    void addMaster();
    void itemChanged(QTableWidgetItem* _item);

private:
    Ui::MastersWidget* m_ui;
    bool m_firstTime;
    QList<Person*> m_clients;
};
}
#endif // MASTERSWIDGET_H
