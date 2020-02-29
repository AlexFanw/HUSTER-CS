#include "res_pro.h"
#include "sys/statfs.h"
#include "ui_res_pro.h"
#include <QTimer>
#include <unistd.h>

res_pro ::res_pro(QWidget *parent):
    QWidget (parent),
    ui(new Ui::res_pro)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    this->move(700,500);

    int pid = getpid();
    ui->CPU->setText(QString::number(pid,10));

    usage = 0;
    ui->CPU_Monitor->setText(QString::number(usage,'f',10));

    QTimer*timer = new QTimer (this);
    connect(timer,SIGNAL(timeout()),this,SLOT(Update()));
    timer->start(1000);

}

void res_pro::Update()
{
    QProcess process;
    process.start("cat /proc/stat");
    process.waitForFinished();
    QString str = process.readLine();
    str.replace("\n","");
    str.replace(QRegExp("( ){1,}")," ");
    auto lst = str.split(" ");
    if(lst.size() > 3)
    {
        double use = lst[1].toDouble() + lst[2].toDouble() + lst[3].toDouble();
        double total = 0;
        for(int i = 1;i < lst.size();++i)
            total += lst[i].toDouble();
        if(total - m_cpu_total__ > 0)
        {
            usage = (use - m_cpu_use__) / (total - m_cpu_total__) * 100.0;

            ui->CPU_Monitor->setText(QString::number(usage,'f',10));
            //qDebug("cpu usage:%.2lf%%",(use - m_cpu_use__) / (total - m_cpu_total__) * 100.0);
            m_cpu_total__ = total;
            m_cpu_use__ = use;
        }
    }
}

res_pro ::~res_pro()
{
    delete ui;
}



