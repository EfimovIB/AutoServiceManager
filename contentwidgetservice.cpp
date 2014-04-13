#include "contentwidgetservice.h"
#include "ui_ContentWidgetService.h"
namespace asmt
{
ContentWidgetService::ContentWidgetService(MainWidget* _mainWidget)
  : ContentWidget(_mainWidget)
  , ui(new Ui::ContentWidgetService)
{
    ui->setupUi(this);
}

ContentWidgetService::ContentWidgetService(ContentWidget* _contentWidget)
  : ContentWidget(_contentWidget)
  , ui(new Ui::ContentWidgetService)
{
    ui->setupUi(this);
}

ContentWidgetService::~ContentWidgetService()
{
    delete ui;
}
}
