#include "res_disk.h"
#include "sys/statfs.h"
#include "ui_res_disk.h"
#include <QTimer>
#include <unistd.h>

res_disk ::res_disk(QWidget *parent):
    QWidget (parent),
    ui(new Ui::res_disk)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    this->move(100,500);

    int pid = getpid();
    ui->Disk->setText(QString::number(pid,10));

    Disk_Used = 0;
    Disk_Free = 0;
    ui->Disk_Monitor->setText(QString::number(Disk_Used,'f',0));
    ui->Disk_Free->setText(QString::number(Disk_Free,'f',0));


    QTimer*timer = new QTimer (this);
    connect(timer,SIGNAL(timeout()),this,SLOT(Update()));
    timer->start(1000);

}

void res_disk::Update()
{
    QProcess process;
    process.start("df -k");
    process.waitForFinished();
    process.readLine();
    while(!process.atEnd())
    {
        QString str = process.readLine();
        if(str.startsWith("/dev/sda"))
        {
            str.replace("\n","");
            str.replace(QRegExp("( ){1,}")," ");
            auto lst = str.split(" ");
            if(lst.size() > 5){
                Disk_Used = lst[2].toDouble()/1024.0;
                ui->Disk_Monitor->setText(QString::number(Disk_Used,'f',0));
                Disk_Free = lst[3].toDouble()/1024.0;
                ui->Disk_Free->setText(QString::number(Disk_Free,'f',0));
            }
                //qDebug("Disk Used:%.0lfMB Free:%.0lfMB",lst[2].toDouble()/1024.0,lst[3].toDouble()/1024.0);
        }
    }
}
res_disk ::~res_disk()
{
    delete ui;
}
