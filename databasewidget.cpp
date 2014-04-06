#include <QDebug>

#include "databasewidget.h"
#include "ui_DatabaseWidget.h"

#include "databasemanager.h"
#include "connection.h"

namespace asmt
{
DatabaseWidget::DatabaseWidget()
  : QWidget()
  , m_ui(new Ui::DatabaseWidget)
  , m_con(new Connection)
{
    m_ui->setupUi(this);

    m_con->connect();
    if (m_con->opened() == false)
        qDebug() << m_con->error();

    m_ui->host->setText(m_con->host());
    m_ui->database->setText(m_con->database());
    m_ui->user->setText(m_con->user());
    m_ui->password->setText(m_con->password());

    m_ui->state->setText(m_con->opened() ? "Open" : "Close");

    connect(m_ui->btnCreateDatabase, SIGNAL(pressed()), SLOT(initDatabase()));
    connect(m_ui->btnDropDatabase,   SIGNAL(pressed()), SLOT(dropDatabase()));

    connect(m_ui->host,     SIGNAL(textEdited(const QString&)), m_con, SLOT(setHost(const QString&)));
    connect(m_ui->database, SIGNAL(textEdited(const QString&)), m_con, SLOT(setDatabase(const QString&)));
    connect(m_ui->user,     SIGNAL(textEdited(const QString&)), m_con, SLOT(setUser(const QString&)));
    connect(m_ui->password, SIGNAL(textEdited(const QString&)), m_con, SLOT(setPassword(const QString&)));

    connect(m_con, SIGNAL(stateChanged(bool)), SLOT(connectStateChanged(bool)));
}

DatabaseWidget::~DatabaseWidget()
{
    delete m_ui;
    delete m_con;
}

void DatabaseWidget::initDatabase() const
{
    DatabaseManager::initTables();
}

void DatabaseWidget::dropDatabase() const
{
    DatabaseManager::dropTables();
}

void DatabaseWidget::connectStateChanged(bool _open)
{
    m_ui->state->setText(_open ? "Open" : "Close");
}

}
