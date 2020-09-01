#include <QApplication>
#include <QDebug>
#include <QMessageBox> //for QT_REQUIRE_VERSION check

#include "mainapp.h"
int main(int argc, char *argv[])
{
    QT_REQUIRE_VERSION(argc, argv, "5.6.0");
    MainApp app(argc, argv);
    if (app.isRunning())
    {
        qDebug()<< "another application is already running";
        return false;
    }
    if (!app.initApp())
    {
        qDebug()<< "start application failed";
    }
    return app.exec();
}
