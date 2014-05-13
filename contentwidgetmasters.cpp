#include "contentwidgetmasters.h"
#include "ui_ContentWidgetMasters.h"
#include "contentwidgetmasterscreator.h"
#include "datastructs.h"
#include "treeitemmodelmasters.h"

namespace asmt
{
ContentWidgetMasters::ContentWidgetMasters(MainWidget* _mainWidget)
  : ContentWidget(_mainWidget)
  , m_ui(new Ui::ContentWidgetMasters)
  , m_creator(NULL)
{
    init();
}

ContentWidgetMasters::ContentWidgetMasters(ContentWidget* _prev)
    : ContentWidget(_prev)
    , m_ui(new Ui::ContentWidgetMasters)
    , m_creator(NULL)
{
    init();
}

void ContentWidgetMasters::topButtonclicked()
{
    if (!m_creator)
    {
        m_creator = new ContentWidgetMastersCreator(this);
        connect(m_creator, SIGNAL(created()), SLOT(updateList()));
    }

    switchOn(m_creator);
}

ContentWidgetMasters::~ContentWidgetMasters()
{
    delete m_ui;
}

void ContentWidgetMasters::init()
{
    m_ui->setupUi(this);
    updateList();
}

void ContentWidgetMasters::updateList()
{
    m_ui->treeView->setModel(new TreeItemModelMasters);
}

}
