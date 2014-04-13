#include "contentwidget.h"
#include "mainwidget.h"

namespace asmt
{

ContentWidget::ContentWidget(MainWidget* _mainWidget)
  : QWidget(_mainWidget)
  , m_mainWidget(_mainWidget)
  , m_prev(NULL)
{
}

ContentWidget::ContentWidget(ContentWidget* _prev)
  : QWidget(_prev->m_mainWidget)
  , m_mainWidget(_prev->m_mainWidget)
  , m_prev(_prev)
{
}

void ContentWidget::switchOn(ContentWidget* _contentWidget)
{
    Q_ASSERT(_contentWidget);

    m_mainWidget->setContent(_contentWidget);
}

void ContentWidget::switchOnPrev()
{
    Q_ASSERT(m_prev);

    switchOn(m_prev);
}

}
