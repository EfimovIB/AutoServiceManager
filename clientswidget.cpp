#include <QDebug>

#include "clientswidget.h"
#include "ui_clientswidget.h"

#include "person.h"
#include "newservicedialog.h"

namespace asmt
{
static const int NameColumn(1);
static const int SurnameColumn(0);
static const int PatronymicColumn(2);
static const int PhoneColumn(3);

ClientsWidget::ClientsWidget()
  : QWidget()
  , m_ui(new Ui::ClientsWidget)
  , m_firstTime(true)
{
    m_ui->setupUi(this);

    m_clients = Person_old::persons(Person_old::Client);

    connect(m_ui->lName, SIGNAL(returnPressed()),                SLOT(addClient()));
    connect(m_ui->table, SIGNAL(itemChanged(QTableWidgetItem*)), SLOT(itemChanged(QTableWidgetItem*)));
    connect(m_ui->newService, SIGNAL(pressed()),                 SLOT(addService()));
}

ClientsWidget::~ClientsWidget()
{
    delete m_ui;
}

void ClientsWidget::showEvent(QShowEvent* _event)
{
    QWidget::showEvent(_event);

    if (m_firstTime)
    {
        updateClientsList();
        correctTableColumnWidth();
        m_firstTime = false;
    }
}

void ClientsWidget::resizeEvent(QResizeEvent* _event)
{
    QWidget::resizeEvent(_event);
    correctTableColumnWidth();
}

void ClientsWidget::addClient()
{
    QString name = m_ui->lName->text();

    if (name.isEmpty())
        return;

    m_ui->lName->clear();

    m_clients << new Person_old(name);

    updateClientsList();
}

void ClientsWidget::updateClientsList()
{
    m_ui->table->setRowCount(m_clients.size());
    for (int i = 0; i < m_clients.size(); ++i)
    {
        QString name = m_clients[i]->name();
        QString surname = m_clients[i]->surname();
        QString patronymic = m_clients[i]->patronymic();
        QStringList phones = m_clients[i]->phones();
        QString phone = phones.isEmpty() ? "" : phones.first();

        m_ui->table->setItem(i, NameColumn,       new QTableWidgetItem(name));
        m_ui->table->setItem(i, SurnameColumn,    new QTableWidgetItem(surname));
        m_ui->table->setItem(i, PatronymicColumn, new QTableWidgetItem(patronymic));
        m_ui->table->setItem(i, PhoneColumn,      new QTableWidgetItem(phone));
    }
}

void ClientsWidget::correctTableColumnWidth()
{
    int width = (m_ui->table->contentsRect().width() - 1) / m_ui->table->columnCount();

    for (int i = 0; i < m_ui->table->columnCount(); ++i)
        m_ui->table->setColumnWidth(i, width);
}

void ClientsWidget::itemChanged(QTableWidgetItem* _item)
{
    Person_old* c = m_clients[_item->row()];

    if (_item->column() == NameColumn)
        c->setName(_item->text());

    if (_item->column() == SurnameColumn)
        c->setSurname(_item->text());

    if (_item->column() == PatronymicColumn)
        c->setPatronymic(_item->text());

    if (_item->column() == PhoneColumn)
        c->setPhones(QStringList() << _item->text());
}

void ClientsWidget::addService()
{
    int r = m_ui->table->currentRow();
    if (-1 == r)
        return;

    NewServiceDialog::createNewService(m_clients[r], this);

    emit serviceAdded();
}

}
