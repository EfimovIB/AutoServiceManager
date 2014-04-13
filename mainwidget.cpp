#include <QVBoxLayout>
#include <QPushButton>

#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "contentwidget.h"

namespace asmt
{
MainWidget::MainWidget()
  : QWidget()
  , m_content(NULL)
{
    m_topButton = new QPushButton(this);
    m_topButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_topButton->setMaximumSize(48,48);
    m_topButton->setMinimumSize(48,48);

    m_bottomButton = new QPushButton(this);
    m_bottomButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_bottomButton->setMaximumSize(48,48);
    m_bottomButton->setMinimumSize(48,48);

    connect(m_topButton, SIGNAL(clicked()), SLOT(topButtonclicked()));
    connect(m_bottomButton, SIGNAL(clicked()), SLOT(bottomButtonclicked()));
}

void MainWidget::setContent(ContentWidget* _content)
{
    if (m_content)
        m_content->hide();

    m_content = _content;

    m_topButton->setIcon(m_content->topButtonIcon());
    m_bottomButton->setIcon(m_content->bottomButtonIcon());

    m_content->lower();

    updatePos();

    m_content->show();
}

void MainWidget::resizeEvent(QResizeEvent *e)
{
    updatePos();
}

void MainWidget::topButtonclicked()
{
    if (m_content)
        m_content->topButtonclicked();
}

void MainWidget::bottomButtonclicked()
{
    if (m_content)
        m_content->bottomButtonclicked();
}

void MainWidget::updatePos()
{
    m_content->setGeometry(0, 0, width(), height());
    m_topButton->move(width() - m_topButton->size().width(), 0);\
    m_bottomButton->move(width() - m_bottomButton->size().width(), height() - m_bottomButton->size().height());\
}
}
