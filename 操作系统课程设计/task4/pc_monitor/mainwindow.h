#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <unistd.h>
#include <QTimer>
#include <sys/sysinfo.h>
#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QWidget>
#include <QList>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList<float> yList;
    QList<float> yList1;

private slots:
    void showinfo(int index);
    void on_pushButton_shutdown_clicked();
    void on_tabWidget_INFO_currentChanged(int index);
    void timer_update_currentTabInfo();
public slots:
    void Update();
private:
    double usage;
    double m_cpu_total__ = 0;
    double m_cpu_used__ = 0;
};

#endif // MAINWINDOW_H
