#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include <QIcon>

namespace asmt
{
class MainWidget;
class ContentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ContentWidget(MainWidget* _mainWidget);
    explicit ContentWidget(ContentWidget* _prev);

    virtual void topButtonclicked() {}
    virtual void bottomButtonclicked() {}

    virtual QIcon topButtonIcon() { return QIcon(); }
    virtual QIcon bottomButtonIcon() { return QIcon(); }

protected:

    void switchOn(ContentWidget* _contentWidget);
    void switchOnPrev();

protected:

    MainWidget* m_mainWidget;

private:

    ContentWidget* m_prev;
};

}
#endif // CONTENTWIDGET_H
