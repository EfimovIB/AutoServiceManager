#include "contentwidgetclientscreator.h"
#include "ui_ContentWidgetClientsCreator.h"

namespace asmt
{

ContentWidgetClientsCreator::ContentWidgetClientsCreator(MainWidget *_mainWidget)
  : ContentWidget(_mainWidget)
  , m_ui(new Ui::ContentWidgetClientsCreator)
{
    m_ui->setupUi(this);
}

ContentWidgetClientsCreator::ContentWidgetClientsCreator(ContentWidget *_contentWidget)
  : ContentWidget(_contentWidget)
  , m_ui(new Ui::ContentWidgetClientsCreator)
{
    m_ui->setupUi(this);
}

ContentWidgetClientsCreator::~ContentWidgetClientsCreator()
{
    delete m_ui;
}

}
