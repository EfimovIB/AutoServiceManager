#include "contentwidgetservice.h"
#include "ui_ContentWidgetService.h"
#include "contentwidgetservicecreator.h"
#include "treeitemmodelservice.h"
#include "datastructs.h"

namespace asmt
{
ContentWidgetService::ContentWidgetService(MainWidget* _mainWidget)
  : ContentWidget(_mainWidget)
  , m_ui(new Ui::ContentWidgetService)
  , m_creatInvoice(NULL)
  , m_model(NULL)
{
    m_ui->setupUi(this);
    m_ui->details->hide();
    m_ui->save->hide();
    updateTreeView();
    connect(m_ui->treeView->selectionModel(), SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), SLOT(currentChanged(const QModelIndex&, const QModelIndex&)));
}

ContentWidgetService::ContentWidgetService(ContentWidget* _contentWidget)
  : ContentWidget(_contentWidget)
  , m_ui(new Ui::ContentWidgetService)
  , m_creatInvoice(NULL)
  , m_model(NULL)
{
    m_ui->setupUi(this);
    m_ui->details->hide();
    m_ui->save->hide();
    updateTreeView();
    connect(m_ui->treeView->selectionModel(), SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), SLOT(currentChanged(const QModelIndex&, const QModelIndex&)));
}

ContentWidgetService::~ContentWidgetService()
{
    delete m_ui;
}

void ContentWidgetService::topButtonclicked()
{
    if (!m_creatInvoice)
    {
        m_creatInvoice = new ContentWidgetServiceCreator(this);

        connect(m_creatInvoice, SIGNAL(created()), SLOT(updateTreeView()));
    }

    switchOn(m_creatInvoice);
}

void ContentWidgetService::updateTreeView()
{
    m_model = new TreeItemModelService();
    m_ui->treeView->setModel(m_model);
}

void ContentWidgetService::currentChanged(const QModelIndex& _current, const QModelIndex& _previous)
{
    m_ui->details->setVisible(_current.isValid());

    if (!m_model || !_current.isValid())
        return;

    unsigned int id = m_model->simplifyService(_current.internalId())->id;

    fillDetails(id);
}

void ContentWidgetService::fillDetails(unsigned int _id)
{
    QSharedPointer<Service> s = Service::service(_id);

    if (!s)
        return;

    m_ui->agregateName->setText(s->aggregate.name);
    m_ui->agregateType->setText(s->aggregate.type.name);
    m_ui->agregateNumber->setText(s->aggregate.number);
    m_ui->car->setText(s->aggregate.car.name);
    m_ui->boxNumber->setText(QString::number(s->boxNumber));
    m_ui->changed->setPlainText(s->changed);

    if (s->person.phone.size() > 0)
        m_ui->telephone->setText(s->person.phone.first());
    m_ui->surname->setText(s->person.surname);
    m_ui->name->setText(s->person.name);
    m_ui->patronymic->setText(s->person.patronymic);
    m_ui->personComments->setPlainText(s->personComments);

    m_ui->startDate->setDate(s->startDate);
    m_ui->endDate->setDate(s->endDate);
    m_ui->mastersComments->setPlainText(s->mastersComments);
    m_ui->price->setValue(s->price);

    // todo firstly: edit & save
}
}
