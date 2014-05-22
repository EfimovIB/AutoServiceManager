#include "contentwidgetsettings.h"
#include "ui_ContentWidgetSettings.h"

#include "databasemanager.h"
#include "connection.h"

namespace asmt
{
ContentWidgetSettings::ContentWidgetSettings(MainWidget* _mainWidget)
  : ContentWidget(_mainWidget)
  , m_ui(new Ui::ContentWidgetSettings)
{
    init();
}

ContentWidgetSettings::ContentWidgetSettings(ContentWidget *_contentWidget)
  : ContentWidget(_contentWidget)
  , m_ui(new Ui::ContentWidgetSettings)
{
    init();
}

ContentWidgetSettings::~ContentWidgetSettings()
{
    delete m_ui;
    delete m_con;
}

void ContentWidgetSettings::init()
{
    m_ui->setupUi(this);

    m_con = new Connection;

    m_ui->host->setText(m_con->host());
    m_ui->port->setText(QString::number(m_con->port()));
    m_ui->database->setText(m_con->database());
    m_ui->user->setText(m_con->user());
    m_ui->password->setText(m_con->password());

    m_ui->state->setText(m_con->opened() ? "Open" : "Close");

    connect(m_ui->btnCreateDatabase,  SIGNAL(pressed()), SLOT(initDatabase()));
    connect(m_ui->btnDropDatabase,    SIGNAL(pressed()), SLOT(dropDatabase()));
    connect(m_ui->btnRecalcWareHouse, SIGNAL(pressed()), SLOT(recalcWareHouse()));

    connect(m_ui->connect, SIGNAL(pressed()), m_con, SLOT(connect()));

    connect(m_ui->host,     SIGNAL(editingFinished()), SLOT(hostChanged()));
    connect(m_ui->port,     SIGNAL(editingFinished()), SLOT(portChanged()));
    connect(m_ui->database, SIGNAL(editingFinished()), SLOT(databaseChanged()));
    connect(m_ui->user,     SIGNAL(editingFinished()), SLOT(userChanged()));
    connect(m_ui->password, SIGNAL(editingFinished()), SLOT(passwordChanged()));

    connect(m_con, SIGNAL(stateChanged(bool)), SLOT(connectStateChanged(bool)));

    m_con->connect();
}

void ContentWidgetSettings::initDatabase() const
{
    DatabaseManager::initTables();
}

void ContentWidgetSettings::dropDatabase() const
{
    DatabaseManager::dropTables();
}

void ContentWidgetSettings::recalcWareHouse() const
{
    DatabaseManager::recalcSpareCount();
}

void ContentWidgetSettings::connectStateChanged(bool _open)
{
    m_ui->state->setText(_open ? "Open" : "Close");
}

void ContentWidgetSettings::hostChanged()
{
    m_con->setHost(m_ui->host->text());
}

void ContentWidgetSettings::portChanged()
{
    m_con->setPort(m_ui->port->text().toUInt());
}

void ContentWidgetSettings::databaseChanged()
{
    m_con->setDatabase(m_ui->database->text());
}

void ContentWidgetSettings::userChanged()
{
    m_con->setUser(m_ui->user->text());
}

void ContentWidgetSettings::passwordChanged()
{
    m_con->setPassword(m_ui->password->text());
}
}
