#ifndef ASM_MAINWINDOW_H
#define ASM_MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

namespace asmt
{
class MainWindow : public QMainWindow
{
public:
    MainWindow();
    ~MainWindow();

private:
    Ui::MainWindow* m_ui;
};
}

#endif //ASM_MAINWINDOW_H
