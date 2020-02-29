#ifndef RES_DISK_H
#define RES_DISK_H

#include <QObject>
#include <QTimer>
#include <QProcess>
#include <QDebug>
#include <QWidget>
#include "ui_res_disk.h"
namespace Ui {
    class res_disk;
}
class res_disk:public QWidget
{
    Q_OBJECT
public:
    explicit res_disk(QWidget *parent = nullptr);
    ~res_disk();
public slots:
    void Update();
private:
    double Disk_Used;
    double Disk_Free;
    Ui::res_disk *ui;
private:
    double m_cpu_use__ = 0;
    double m_cpu_total__ = 0;

};

#endif // RES_DISK_H
