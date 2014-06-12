#include <QDebug>

#include "contentwidgethome.h"
#include "ui_ContentWidgetHome.h"
#include "contentwidgetservice.h"
#include "contentwidgetclients.h"
#include "contentwidgetwarehouse.h"
#include "contentwidgetsettings.h"
#include "contentwidgetmasters.h"


namespace asmt
{

ContentWidgetHome::ContentWidgetHome(MainWidget* _mainWidget)
  : ContentWidget(_mainWidget)
  , m_ui(new Ui::ContentWidgetHome)
  , m_service(NULL)
  , m_clients(NULL)
  , m_warehouse(NULL)
  , m_settings(NULL)
  , m_masters(NULL)
{
    m_ui->setupUi(this);

    connect(m_ui->service,   SIGNAL(clicked()), SLOT(serviceClicked()));
    connect(m_ui->clients, SIGNAL(clicked()), SLOT(clientsClicked()));
    connect(m_ui->warehouse, SIGNAL(clicked()), SLOT(warehouseClicked()));
    connect(m_ui->settings,  SIGNAL(clicked()), SLOT(settingsClicked()));
    connect(m_ui->masters,   SIGNAL(clicked()), SLOT(mastersClicked()));
}

ContentWidgetHome::ContentWidgetHome(ContentWidget* _contentWidget)
  : ContentWidget(_contentWidget)
{}

ContentWidgetHome::~ContentWidgetHome()
{
    delete m_ui;
}

void ContentWidgetHome::serviceClicked()
{
    if (!m_service)
        m_service = new ContentWidgetService(this);

    switchOn(m_service);
}

void ContentWidgetHome::clientsClicked()
{
    if (!m_clients)
        m_clients = new ContentWidgetClients(this);

    switchOn(m_clients);
}

void ContentWidgetHome::warehouseClicked()
{
    if (!m_warehouse)
        m_warehouse = new ContentWidgetWareHouse(this);

    switchOn(m_warehouse);
}

void ContentWidgetHome::settingsClicked()
{
    if (!m_settings)
        m_settings = new ContentWidgetSettings(this);

    switchOn(m_settings);
}

void ContentWidgetHome::mastersClicked()
{
    if (!m_masters)
        m_masters = new ContentWidgetMasters(this);

    switchOn(m_masters);
}

}
