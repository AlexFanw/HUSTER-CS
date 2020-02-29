#ifndef RES_MEM_H
#define RES_MEM_H
#include <QObject>
#include <QTimer>
#include <QProcess>
#include <QDebug>
#include <QWidget>
#include "ui_res_mem.h"
namespace Ui {
    class res_mem;
}
class res_mem:public QWidget
{
    Q_OBJECT
public:
    explicit res_mem(QWidget *parent = nullptr);
    ~res_mem();
public slots:
    void Update();
private:
    double Mem_Used;
    double Mem_Free;
    Ui::res_mem *ui;


};
#endif // RES_MEM_H
