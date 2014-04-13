#include "contentwidgetaccounting.h"
#include "ui_ContentWidgetAccounting.h"

namespace asmt
{
ContentWidgetAccounting::ContentWidgetAccounting(MainWidget* _mainWidget)
  : ContentWidget(_mainWidget)
  , m_ui(new Ui::ContentWidgetAccounting)
{
    m_ui->setupUi(this);
    connect(m_ui->masters, SIGNAL(clicked()), SLOT(mastersClicked()));
    connect(m_ui->spare,   SIGNAL(clicked()), SLOT(spareClicked()));
}

ContentWidgetAccounting::ContentWidgetAccounting(ContentWidget* _prev)
    : ContentWidget(_prev)
    , m_ui(new Ui::ContentWidgetAccounting)
{
    m_ui->setupUi(this);
}

ContentWidgetAccounting::~ContentWidgetAccounting()
{
    delete m_ui;
}

void ContentWidgetAccounting::mastersClicked()
{

}

void ContentWidgetAccounting::spareClicked()
{

}
}
