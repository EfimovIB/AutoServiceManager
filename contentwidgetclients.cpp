#include <QDebug>

#include "contentwidgetclients.h"
#include "contentwidgetmasterscreator.h"
#include "ui_ContentWidgetClients.h"
#include "treeitemmodelclients.h"

namespace asmt
{
ContentWidgetClients::ContentWidgetClients(MainWidget* _mainWidget)
  : ContentWidget(_mainWidget)
  , m_ui(new Ui::ContentWidgetClients)
  , m_creator(NULL)
{
    init();
}

ContentWidgetClients::ContentWidgetClients(ContentWidget* _contentWidget)
  : ContentWidget(_contentWidget)
  , m_ui(new Ui::ContentWidgetClients)
  , m_creator(NULL)
{
    init();
}

ContentWidgetClients::~ContentWidgetClients()
{
    delete m_ui;
}

void ContentWidgetClients::topButtonclicked()
{
    if (!m_creator)
        m_creator = new ContentWidgetMastersCreator(this, false);

    switchOn(m_creator);
}

void ContentWidgetClients::updateTree()
{
    m_ui->treeView->setModel(new TreeItemModelClients);
}

void ContentWidgetClients::init()
{
    m_ui->setupUi(this);

    connect(m_creator, SIGNAL(created()), SLOT(updateList()));

    updateTree();
}

}
