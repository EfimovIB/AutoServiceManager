#include <QDebug>

#include "contentwidgethome.h"
#include "ui_ContentWidgetHome.h"
#include "contentwidgetservice.h"
#include "contentwidgetwarehouse.h"
#include "contentwidgetsettings.h"
#include "contentwidgetaccounting.h"

namespace asmt
{

ContentWidgetHome::ContentWidgetHome(MainWidget* _mainWidget)
  : ContentWidget(_mainWidget)
  , m_ui(new Ui::ContentWidgetHome)
  , m_service(NULL)
  , m_warehouse(NULL)
  , m_settings(NULL)
  , m_accounting(NULL)
{
    m_ui->setupUi(this);

    connect(m_ui->service,   SIGNAL(clicked()), SLOT(serviceClicked()));
    connect(m_ui->warehouse, SIGNAL(clicked()), SLOT(warehouseClicked()));
    connect(m_ui->settings,  SIGNAL(clicked()), SLOT(settingsClicked()));
    connect(m_ui->accounting,  SIGNAL(clicked()), SLOT(accountingClicked()));
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

void ContentWidgetHome::accountingClicked()
{
    if (!m_accounting)
        m_accounting = new ContentWidgetAccounting(this);

    switchOn(m_accounting);
}

}