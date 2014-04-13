#include "contentwidgetwarehouse.h"
#include "ui_ContentWidgetWareHouse.h"

namespace asmt
{

ContentWidgetWareHouse::ContentWidgetWareHouse(MainWidget* _mainWidget)
  : ContentWidget(_mainWidget)
  , ui(new Ui::ContentWidgetWareHouse)
{
    ui->setupUi(this);
}

ContentWidgetWareHouse::ContentWidgetWareHouse(ContentWidget *_contentWidget)
  : ContentWidget(_contentWidget)
  , ui(new Ui::ContentWidgetWareHouse)
{
    ui->setupUi(this);
}

ContentWidgetWareHouse::~ContentWidgetWareHouse()
{
    delete ui;
}

}
