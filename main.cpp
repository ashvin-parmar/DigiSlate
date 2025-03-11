#include "mainwindow.h"

#include <QApplication>
#include <QTimer>
#include <QSplashScreen>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPixmap pixmap(":/images/icon2/splash.png");
    QSplashScreen splash(pixmap.scaled(800,800,Qt::KeepAspectRatio));
    splash.show();
    app.processEvents();
//    int x;
//    scanf("%d",&x);
    MainWindow w;
    w.show();
    splash.finish(&w);
    return app.exec();
}
