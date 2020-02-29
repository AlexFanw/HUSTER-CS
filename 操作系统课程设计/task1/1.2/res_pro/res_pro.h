#ifndef RES_PRO_H
#define RES_PRO_H

#include <QObject>
#include <QTimer>
#include <QProcess>
#include <QDebug>
#include <QWidget>
#include "ui_res_pro.h"
namespace Ui {
    class res_pro;
}
class res_pro:public QWidget
{
    Q_OBJECT
public:
    explicit res_pro(QWidget *parent = nullptr);
    ~res_pro();
public slots:
    void Update();
private:
    double usage;
    Ui::res_pro *ui;
private:
    double m_cpu_use__ = 0;
    double m_cpu_total__ = 0;

};

#endif // res_pro_h
