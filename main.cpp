#include <QtGui>
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    translator.load("./ts_ru.qm");
    app.installTranslator(&translator);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("CP1251"));

    asmt::MainWindow w;
    w.show();

    return app.exec();
}
