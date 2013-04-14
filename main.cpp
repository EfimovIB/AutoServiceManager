#include <QtGui>

#include "mainwindow.h"

 int main(int argc, char *argv[])
 {
     QApplication app(argc, argv);
  
     QTranslator translator;
     translator.load(QString("arrowpad_") );
     app.installTranslator(&translator);

	asmt::MainWindow w;
	w.show();

     return app.exec();
 }