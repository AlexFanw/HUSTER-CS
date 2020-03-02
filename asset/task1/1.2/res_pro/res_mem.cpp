#include "res_mem.h"
#include "sys/statfs.h"
#include "ui_res_mem.h"
#include <QTimer>
#include <unistd.h>

res_mem ::res_mem(QWidget *parent):
    QWidget (parent),
    ui(new Ui::res_mem)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    this->move(1300,500);

    int pid = getpid();
    ui->Mem->setText(QString::number(pid,10));

    Mem_Used = 0;
    Mem_Free = 0;
    ui->Mem_Monitor->setText(QString::number(Mem_Used,'f',0));
    ui->Mem_Free->setText(QString::number(Mem_Free,'f',0));


    QTimer*timer = new QTimer (this);
    connect(timer,SIGNAL(timeout()),this,SLOT(Update()));
    timer->start(1000);

}
void res_mem::Update()
{
    QProcess process;
    process.start("free -m");             //使用free完成获取
    process.waitForFinished();
    process.readLine();
    QString str = process.readLine();
    str.replace("\n","");
    str.replace(QRegExp("( ){1,}")," ");//将连续空格替换为单个空格 用于分割
    auto lst = str.split(" ");
    if(lst.size() > 6)
    {
        Mem_Used = lst[1].toDouble();
        ui->Mem_Monitor->setText(QString::number(Mem_Used,'f',0));
        Mem_Free = lst[6].toDouble();
        ui->Mem_Free->setText(QString::number(Mem_Free,'f',0));
        //qDebug("Mem Total:%.0lfMB Free:%.0lfMB",lst[1].toDouble(),lst[6].toDouble());
    }
}
res_mem ::~res_mem()
{
    delete ui;
}
