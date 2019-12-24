#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QListWidget>
#include<tcpserver.h>
#include<socketthread.h>
#include<QTimer>
#include<QTime>

#include"tltipwidget.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void updateListViewSignal();
public slots:
    void updateListViewSlot();
    void startBtnClicked();
    void endBtnClicked();
    void updateTime();
    void portModifyClicked();
    void configClicked();
    void close_btn_clicked();
    void max_btn_clicked();
    void mini_btn_clicked();
protected:
    void mousePressEvent(QMouseEvent *event);//按下
    void mouseMoveEvent(QMouseEvent *event);//移动
    void mouseReleaseEvent(QMouseEvent *event);//抬起
    bool m_draging;//是否拖动
    QPoint m_startPostion;//拖动前鼠标位置
    QPoint m_framPostion;//窗体的原始位置
private:
    Ui::MainWindow *ui;
    SocketThread * socketThread;
    TLTipsWidget* tipsWidget;
    void init();
    void initVariable();
    void initTimer();
    void initBtn();
    void initStyleSheets();
    void initTableView();
    bool isModifyPort;
    QAbstractItemModel* model;
    QTimer*timer;
    QTime * timeRecord;
};

#endif // MAINWINDOW_H
