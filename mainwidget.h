#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
class QVBoxLayout;
class QPushButton;
namespace Ui
{
    class MainWidget;
}

namespace asmt
{
class ContentWidget;
class MainWidget : public QWidget
{
    Q_OBJECT

public:

    MainWidget();

    void setContent(ContentWidget* _content);

protected:

    void resizeEvent(QResizeEvent* e);

private slots:

    void topButtonclicked();
    void bottomButtonclicked();

private:

    void updatePos();

private:

    ContentWidget* m_content;
    QPushButton* m_bottomButton;
    QPushButton* m_topButton;
};
}
#endif // MAINWIDGET_H
