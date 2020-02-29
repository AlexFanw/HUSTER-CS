#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include "res_pro.h"
#include "res_disk.h"
#include "res_mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    int pid;
    if((pid = fork()) == 0){
        QApplication a(argc,argv);
        res_pro w;
        w.setWindowTitle("Alex Fan's CPU Monitor");
        w.show();
        a.exec();
        exit(0);
    }
    if((pid = fork()) == 0){
        QApplication a(argc,argv);
        res_disk w;
        w.setWindowTitle("Alex Fan's DISK Monitor");
        w.show();
        a.exec();
        exit(0);
    }
    if((pid = fork()) == 0){
        QApplication a(argc,argv);
        res_mem w;
        w.setWindowTitle("Alex Fan's MEM Monitor");
        w.show();
        a.exec();
        exit(0);
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Alex Fan's Time Monitor");
    w.show();

    return a.exec();
}
