#include "mainwindow.h"

#include <QApplication>
#include <QTimer>
#include <QSplashScreen>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QApplication a(argc, argv);
    QPixmap pixmap("splash.jpg");
    QSplashScreen splash(pixmap);
   // splash.setGeometry(0,0,1370,700);
    splash.show();
    QTimer::singleShot(50000,&splash,&QWidget::close);

    MainWindow w;
    w.show();
    return app.exec();
}
