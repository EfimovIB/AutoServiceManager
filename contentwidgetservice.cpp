#include "contentwidgetservice.h"
#include "ui_ContentWidgetService.h"
#include "contentwidgetservicecreator.h"
#include "treeitemmodelservice.h"
#include "datastructs.h"
#include "databasemanager.h"

namespace asmt
{
ContentWidgetService::ContentWidgetService(MainWidget* _mainWidget)
  : ContentWidget(_mainWidget)
  , m_ui(new Ui::ContentWidgetService)
  , m_creatInvoice(NULL)
  , m_model(NULL)
  , m_service(NULL)
{
    init();
}

ContentWidgetService::ContentWidgetService(ContentWidget* _contentWidget)
  : ContentWidget(_contentWidget)
  , m_ui(new Ui::ContentWidgetService)
  , m_creatInvoice(NULL)
  , m_model(NULL)
  , m_service(NULL)
{
    init();
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

void ContentWidgetService::init()
{
    m_ui->setupUi(this);
    m_ui->details->hide();
    m_ui->save->hide();
    updateTreeView();

    connect(m_ui->edit, SIGNAL(toggled(bool)), SLOT(edit()));
    connect(m_ui->save, SIGNAL(clicked(bool)), SLOT(save()));

    connect(m_ui->agregateName,    SIGNAL(textEdited(const QString&)), SLOT(agregateNameChanged()));
    connect(m_ui->agregateType,    SIGNAL(textEdited(const QString&)), SLOT(agregateTypeChanged()));
    connect(m_ui->agregateNumber,  SIGNAL(textEdited(const QString&)), SLOT(agregateNumberChanged()));
    connect(m_ui->car,             SIGNAL(textEdited(const QString&)), SLOT(carChanged()));
    connect(m_ui->boxNumber,       SIGNAL(textEdited(const QString&)), SLOT(boxNumberChanged()));
    connect(m_ui->changed,         SIGNAL(textChanged()),               SLOT(changedChanged()));//???
    connect(m_ui->telephone,       SIGNAL(textEdited(const QString&)), SLOT(telephoneChanged()));
    connect(m_ui->surname,         SIGNAL(textEdited(const QString&)), SLOT(surnameChanged()));
    connect(m_ui->name,            SIGNAL(textEdited(const QString&)), SLOT(nameChanged()));
    connect(m_ui->patronymic,      SIGNAL(textEdited(const QString&)), SLOT(patronymicChanged()));
    connect(m_ui->personComments,  SIGNAL(textChanged()),                     SLOT(personCommentsChanged()));
    connect(m_ui->startDate,       SIGNAL(dateTimeChanged(const QDateTime&)), SLOT(startDateChanged()));
    connect(m_ui->endDate,         SIGNAL(dateTimeChanged(const QDateTime&)), SLOT(endDateChanged()));
    connect(m_ui->mastersComments, SIGNAL(textChanged()), SLOT(mastersCommentsChanged()));
    connect(m_ui->price,           SIGNAL(valueChanged(const QString&)), SLOT(priceChanged()));

    // todo firstly: edit & save
}

void ContentWidgetService::fillDetails(unsigned int _id)
{
    m_service = Service::service(_id);

    if (!m_service)
        return;

    m_ui->agregateName->setText(m_service->aggregate.name);
    m_ui->agregateType->setText(m_service->aggregate.type.name);
    m_ui->agregateNumber->setText(m_service->aggregate.number);
    m_ui->car->setText(m_service->aggregate.car.name);
    m_ui->boxNumber->setText(QString::number(m_service->boxNumber));
    m_ui->changed->setPlainText(m_service->changed);

    if (m_service->person.phone.size() > 0)
        m_ui->telephone->setText(m_service->person.phone.first());
    m_ui->surname->setText(m_service->person.surname);
    m_ui->name->setText(m_service->person.name);
    m_ui->patronymic->setText(m_service->person.patronymic);
    m_ui->personComments->setPlainText(m_service->personComments);

    m_ui->startDate->setDate(m_service->startDate);
    m_ui->endDate->setDate(m_service->endDate);
    m_ui->mastersComments->setPlainText(m_service->mastersComments);
    m_ui->price->setValue(m_service->price);
}

void ContentWidgetService::updateTreeView()
{
    m_model = new TreeItemModelService();

    m_ui->treeView->setModel(m_model);

    connect(m_ui->treeView->selectionModel(), SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), SLOT(currentChanged(const QModelIndex&, const QModelIndex&)), Qt::UniqueConnection);
}

void ContentWidgetService::currentChanged(const QModelIndex& _current, const QModelIndex& _previous)
{
    m_ui->details->setVisible(_current.isValid());

    if (!m_model || !_current.isValid())
        return;

    unsigned int id = m_model->simplifyService(_current.internalId())->id;

    fillDetails(id);
}

void ContentWidgetService::edit()
{
    m_ui->save->setVisible(m_ui->edit->isChecked());
}

void ContentWidgetService::save()
{
    if (!m_service)
        return;

    QString text;

    foreach (QString q, m_changes.values())
        if (!q.isEmpty())
            text += q + ";";

    if (!text.isEmpty())
        DatabaseManager::execQuery(text); // todo: inform user about results
}

void ContentWidgetService::agregateNameChanged()
{
    if (!m_service)
        return;

    QString text = m_service->aggregate.name == m_ui->agregateName->text() ? "" : "update " + AggregateTableName + " set name='" + m_ui->agregateName->text() + "' where id=" + QString::number(m_service->aggregate.id);

    m_changes[m_ui->agregateName->objectName()] = text;
}

void ContentWidgetService::agregateTypeChanged()
{
    if (!m_service)
        return;

    QString text = m_service->aggregate.type.name == m_ui->agregateType->text() ? "" : "select * from setAggregateTypeForId('" + m_ui->agregateType->text() + "', " + QString::number(m_service->aggregate.id) + ");";

    m_changes[m_ui->agregateType->objectName()] = text;
}

void ContentWidgetService::agregateNumberChanged()
{

}

void ContentWidgetService::carChanged()
{

}

void ContentWidgetService::boxNumberChanged()
{

}

void ContentWidgetService::changedChanged()
{

}

void ContentWidgetService::telephoneChanged()
{

}

void ContentWidgetService::surnameChanged()
{

}

void ContentWidgetService::nameChanged()
{

}

void ContentWidgetService::patronymicChanged()
{

}

void ContentWidgetService::personCommentsChanged()
{

}

void ContentWidgetService::startDateChanged()
{

}

void ContentWidgetService::endDateChanged()
{

}

void ContentWidgetService::mastersCommentsChanged()
{

}

void ContentWidgetService::priceChanged()
{

}

}
