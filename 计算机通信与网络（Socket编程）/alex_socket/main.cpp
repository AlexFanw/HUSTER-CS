#include "mainwindow.h"
#include <QApplication>
#include"commonhelper.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CommonHelper::setStyle(":/images/black.css");
    MainWindow w;
    w.show();

    return a.exec();
}
