#include <QtGui>
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>

//#include "mainwindow.h"
#include "mainwidget.h"
#include "contentwidgethome.h"
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    translator.load("./ts_ru.qm");
    app.installTranslator(&translator);

    QTextCodec* codec = QTextCodec::codecForName("UTF8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);

    using namespace asmt;
//    asmt::MainWindow w;
//    w.show();

    Connection c;
    c.connect();

    MainWidget w;
    ContentWidgetHome* h = new ContentWidgetHome(&w);
    w.setContent(h);
    w.show();

    return app.exec();
}
