#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTimer>
#include <QDateTime>
#include <QMainWindow>
#include <res_pro.h>
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

public slots:
    void timerUpdate(void);


};

#endif // MAINWINDOW_H
