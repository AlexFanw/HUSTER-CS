#include "tltipwidget.h"
#include <QPainter>

TLTipsWidget::TLTipsWidget(QWidget *parent) :
    QWidget(parent),
    m_pLabel(NULL),
    m_pTimer(NULL),
    m_pCloseTimer(NULL),
    m_dTransparent(1.0)
{
    this->setFixedHeight(55);
    m_pLabel = new QLabel(this);
    m_pLabel->setFixedHeight(55);
    m_pLabel->move(0,0);
    m_pLabel->setAlignment(Qt::AlignCenter);
    m_pLabel->setStyleSheet("color:white;background:rgb(0, 160, 230);");
    this->hide();
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
//    this->setAttribute(,true);

    m_pTimer = new QTimer();
    m_pTimer->setInterval(3000);
    m_pCloseTimer = new QTimer();
    m_pCloseTimer->setInterval(20);
    connect(m_pTimer,&QTimer::timeout,this,&TLTipsWidget::onTimerStayOut);
    connect(m_pCloseTimer,&QTimer::timeout,this,&TLTipsWidget::onTimerCloseOut);
}

TLTipsWidget::~TLTipsWidget()
{
    delete m_pTimer;
    delete m_pCloseTimer;
}

void TLTipsWidget::setText(const QString &text){
    QFontMetrics fm(this->font());
    int width = fm.width(text) * 1.2;
    this->setFixedWidth(width);
    m_pLabel->setFixedWidth(width);
    this->m_pLabel->setText(text);
    this->show();
    m_pTimer->start();
}


void TLTipsWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
//    painter.setPen(Qt::NoPen);
    painter.setPen(QPen(QColor(Qt::blue),2));
    //painter.setBrush(QColor(0,0,0,180));
    painter.setBrush(Qt::red);
    painter.drawRoundedRect(rect(),5,5);
    QWidget::paintEvent(e);
}

void TLTipsWidget::showEvent(QShowEvent *e)
{
    QTimer::singleShot(2500,this,SLOT(hide()));
    this->move(parentWidget()->width() / 2 - this->width()/2,
               (parentWidget()->height()*(1- (172/1120))) / 2 - this->height() / 2);
    QWidget::showEvent(e);
}

void TLTipsWidget::onTimerStayOut()
{
    m_pTimer->stop();
    if(m_pCloseTimer->isActive()){
        m_pCloseTimer->stop();
    }
    m_pCloseTimer->start();
}

void TLTipsWidget::onTimerCloseOut()
{
    m_dTransparent -= 0.01;
    if(m_dTransparent <= 0.0001)
    {
        m_pCloseTimer->stop();
        this->hide();
        m_pLabel->clear();
    }
    else
    {
        setWindowOpacity(m_dTransparent);
    }
}
