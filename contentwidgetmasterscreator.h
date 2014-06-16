#ifndef CONTENTWIDGETMASTERSCREATOR_H
#define CONTENTWIDGETMASTERSCREATOR_H

#include "contentwidget.h"

namespace Ui
{
    class ContentWidgetMastersCreator;
}

namespace asmt
{

class ContentWidgetMastersCreator : public ContentWidget
{
    Q_OBJECT

public:

    explicit ContentWidgetMastersCreator(MainWidget* _mainWidget, bool masterCreator);
    explicit ContentWidgetMastersCreator(ContentWidget* _prev, bool masterCreator);
    ~ContentWidgetMastersCreator();

    void topButtonclicked();
    void bottomButtonclicked();

    QIcon topButtonIcon() { return QIcon(":/button/pictures/accept.png"); }
    QIcon bottomButtonIcon() { return QIcon(":/button/pictures/reject.png"); }

signals:

    void created();

private:

    void init();
    bool insertDataInDatabase();
    bool dataEnough() const;
    void clearForm();

private:

    Ui::ContentWidgetMastersCreator* m_ui;

    bool m_masterCreator;
};

}

#endif // CONTENTWIDGETMASTERSCREATOR_H
