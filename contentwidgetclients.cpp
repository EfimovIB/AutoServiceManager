#include <QDebug>

#include "contentwidgetclients.h"
#include "contentwidgetclientscreator.h"
#include "ui_ContentWidgetClients.h"

namespace asmt
{
ContentWidgetClients::ContentWidgetClients(MainWidget* _mainWidget)
  : ContentWidget(_mainWidget)
  , m_ui(new Ui::ContentWidgetClients)
  , m_creator(NULL)
{
    m_ui->setupUi(this);
}

ContentWidgetClients::ContentWidgetClients(ContentWidget* _contentWidget)
  : ContentWidget(_contentWidget)
  , m_ui(new Ui::ContentWidgetClients)
  , m_creator(NULL)
{
    m_ui->setupUi(this);
}

ContentWidgetClients::~ContentWidgetClients()
{
    delete m_ui;
}

void ContentWidgetClients::topButtonclicked()
{
    if (!m_creator)
        m_creator = new ContentWidgetClientsCreator(this);

    switchOn(m_creator);
}

}
