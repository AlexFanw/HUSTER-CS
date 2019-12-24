#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QStringListModel>
#include<tcpserver.h>
#include<config.h>
#include<QFileDialog>
#include<QDebug>
#include<QApplication>
#include<global.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    ui->mainToolBar->hide();
    init();
}

MainWindow::~MainWindow()
{
    delete tipsWidget;
    delete timer;
    delete timeRecord;
    delete ui;
}

void MainWindow::init(){
    this->socketThread=0;
    //QStringList strList;
    //strList<<"Monday"<<"Tuesday"<<"Wednesday"<<"Thursday"<<"Friday"<<"Saterday";
    //this->model=new QStringListModel(strList);
    //this->ui->listView->setModel(this->model);
    this->ui->lineEdit->setEnabled(false);
    this->ui->lineEdit->setText(QString::number(Config::port));
    initVariable();
    initBtn();
    initTableView();
    initStyleSheets();
    initTimer();

}
void MainWindow::initTableView(){

//     pthread_mutex_init(&(Global::sMux),NULL);
    this->ui->tableView->verticalHeader()->setDefaultSectionSize(40);
    this->ui->tableView->horizontalHeader()->setDefaultSectionSize(133);

    Global::model->setHorizontalHeaderLabels(Global::tableTitleLabels);
    this->ui->tableView->setModel(Global::model);
    this->ui->tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);//对第0列单独设置固定宽度
    this->ui->tableView->setColumnWidth(3, 350);//设置固定宽度
}
void MainWindow::initStyleSheets(){
    //QPixmap pic(":/images/max.png");
   //ui->titleIcon->setIcon(QIcon(":/images/titleIcon.jpg"));
    //ui->titleIcon->setStyleSheet("QPushButton{width:40px;height:40px;padding:0px;border:1px solid rgb(0, 160, 230);border-radius:5px}");
}
void MainWindow::initVariable(){
    this->isModifyPort=false;      //端口修改模式false
    this->tipsWidget=new TLTipsWidget(this);//对消息框进行初始化
}
void MainWindow::initBtn(){
    //将停止按钮disable
    ui->end_btn->setEnabled(false);
    std::cout<<"ui init"<<std::endl;

    ui->close_btn->setIcon(QIcon(":/images/close.png"));

    ui->close_btn->setStyleSheet("QPushButton{border:none;background-color:#212121;width:20px;height:20px;padding:0.5px;}");

    connect(this->ui->close_btn,SIGNAL(clicked()),this,SLOT(close_btn_clicked()));
    //函数关联
    connect(this->ui->start_btn,SIGNAL(clicked()),this,SLOT(startBtnClicked()));
    connect(this->ui->end_btn,SIGNAL(clicked()),this,SLOT(endBtnClicked()));
    connect(this->ui->port_modify_btn,SIGNAL(clicked()),this,SLOT(portModifyClicked()));
    //connect(this->ui->config_btn,SIGNAL(clicked()),this,SLOT(configClicked()));
}
void MainWindow::max_btn_clicked(){
    setWindowState(Qt::WindowMaximized);
}
void MainWindow::mini_btn_clicked(){
    setWindowState(Qt::WindowMinimized);
}

void MainWindow::close_btn_clicked(){
    qApp->exit(0);
}
//初始化时间函数
void MainWindow::initTimer(){
    this->timer=new QTimer();
    this->timeRecord=new QTime(0,0,0);//初始化时间
    //this->ui->timer->setDigitCount(8);
    //ui->timer->setSegmentStyle(QLCDNumber::Flat);
    //ui->timer->display(timeRecord->toString("hh:mm:ss"));
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
}

//void MainWindow::updateTime(){
   // *timeRecord = timeRecord->addSecs(1);
    //ui->timer->display(timeRecord->toString("hh:mm:ss"));
//}

//开始槽函数
void MainWindow::startBtnClicked(){
    this->socketThread=new SocketThread();
    this->socketThread->start();
    this->ui->start_btn->setEnabled(false);
    this->ui->end_btn->setEnabled(true);
    timer->start(1000);
    tipsWidget->setText("Server Start");
}

//停止槽函数函数
void MainWindow::endBtnClicked(){
    if(this->socketThread==0){
        return;
    }
    std::cout<<"socket thread is not null"<<std::endl;
    this->socketThread->endThread();
    this->socketThread->quit();
    this->socketThread->exit();
    this->socketThread->terminate();
    qDebug("thread stop");
    this->ui->end_btn->setEnabled(false);
    this->ui->start_btn->setEnabled(true);
    this->timer->stop();
    this->tipsWidget->setText("Server Stop");
}

//修改端口槽函数
void MainWindow::portModifyClicked(){
    if(!this->isModifyPort){
      this->ui->lineEdit->setEnabled(true);
        endBtnClicked();   //关闭线程
        this->ui->end_btn->setEnabled(false);//设置endbtn按钮状态
        this->ui->start_btn->setEnabled(false);
      this->ui->port_modify_btn->setText("confirm");
      //this->ui->config_btn->setText("cancel");
      this->isModifyPort=true;
    }else{
        //todo 修改端口
        QString newPort=this->ui->lineEdit->text();
        Config::port=newPort.toInt();
        //todo 实际修改端口
        this->ui->start_btn->setEnabled(true);  //开始按钮激活
        /////////////////////////
        this->ui->lineEdit->setEnabled(false);
        this->ui->port_modify_btn->setText("CHANGE PORT");
        //this->ui->config_btn->setText("CHANGE HTML PATH");
        this->isModifyPort=false;
        this->tipsWidget->setText("Port valid");
    }
}

//修改初始化目录槽函数
void MainWindow::configClicked(){
    if(!this->isModifyPort){
        //修改目录操作

        QString dir=QFileDialog::getExistingDirectory(this,tr("Open Directory"),
                                                      "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if(dir!=NULL){
            Config::tableOfFiles=dir;
            qDebug((const char *)Config::tableOfFiles.toLocal8Bit());
            tipsWidget->setText("successful");
        }else{
            tipsWidget->setText("cancel");
        }
    }else{
        this->ui->port_modify_btn->setText("CHANGE PORT");
        //this->ui->config_btn->setText("CHANGE HTML PATH");
        this->ui->lineEdit->setText(QString::number(Config::port));
        this->ui->lineEdit->setEnabled(false);
        this->ui->start_btn->setEnabled(true);  //开始按钮激活
        this->isModifyPort=false;
        tipsWidget->setText("cancel");
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton)
        {
            //offset 偏移位置
            QPoint offset = event->globalPos() - m_startPostion;
            move(m_framPostion + offset);
        }
        QWidget::mouseMoveEvent(event);//调用父类函数保持原按键行为
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    m_draging = true;
        if(event->buttons() & Qt::LeftButton)//只响应鼠标左键
        {
            m_startPostion = event->globalPos();
            m_framPostion = frameGeometry().topLeft();
        }
        QWidget::mousePressEvent(event);//调用父类函数保持原按键行为
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    m_draging = false;
        QWidget::mouseReleaseEvent(event);
}
