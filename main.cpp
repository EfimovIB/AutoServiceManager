#include <QtGui>
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>

//#include "mainwindow.h"
#include "mainwidget.h"
#include "contentwidgethome.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    QTranslator translator;
    translator.load("./ts_ru.qm");
    app.installTranslator(&translator);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("CP1251"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("CP1251"));

    using namespace asmt;
//    asmt::MainWindow w;
//    w.show();

    MainWidget w;
    ContentWidgetHome* h = new ContentWidgetHome(&w);
    w.setContent(h);
    w.show();

    return app.exec();
}
