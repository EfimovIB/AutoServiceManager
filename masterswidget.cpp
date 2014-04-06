#include "masterswidget.h"
#include "ui_masterswidget.h"

#include "person.h"

namespace asmt
{

static const int NameColumn(1);
static const int SurnameColumn(0);
static const int PatronymicColumn(2);
static const int PhoneColumn(3);

MastersWidget::MastersWidget(QWidget *parent)
  : QWidget(parent)
  , m_ui(new Ui::MastersWidget)
{
    m_ui->setupUi(this);

    m_clients = Person::persons(Person::Master);

    connect(m_ui->lName, SIGNAL(returnPressed()),                SLOT(addMaster()));
    connect(m_ui->table, SIGNAL(itemChanged(QTableWidgetItem*)), SLOT(itemChanged(QTableWidgetItem*)));
}

MastersWidget::~MastersWidget()
{
    delete m_ui;
}

void MastersWidget::showEvent(QShowEvent *_event)
{
    QWidget::showEvent(_event);

    if (m_firstTime)
    {
        updateMastersList();
        correctTableColumnWidth();
        m_firstTime = false;
    }
}

void MastersWidget::resizeEvent(QResizeEvent *_event)
{
    QWidget::resizeEvent(_event);
    correctTableColumnWidth();
}

void MastersWidget::addMaster()
{
    QString name = m_ui->lName->text();

    if (name.isEmpty())
        return;

    m_ui->lName->clear();

    m_clients << new Person(name, Person::Master);

    updateMastersList();
}

void MastersWidget::updateMastersList()
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

void MastersWidget::correctTableColumnWidth()
{
        int width = (m_ui->table->contentsRect().width() - 1) / m_ui->table->columnCount();

        for (int i = 0; i < m_ui->table->columnCount(); ++i)
            m_ui->table->setColumnWidth(i, width);
}

void MastersWidget::itemChanged(QTableWidgetItem *_item)
{
    Person* c = m_clients[_item->row()];

    if (_item->column() == NameColumn)
        c->setName(_item->text());

    if (_item->column() == SurnameColumn)
        c->setSurname(_item->text());

    if (_item->column() == PatronymicColumn)
        c->setPatronymic(_item->text());

    if (_item->column() == PhoneColumn)
        c->setPhones(QStringList() << _item->text());
}
}
