#ifndef TLTIPWIDGET_H
#define TLTIPWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QTimer>

class TLTipsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TLTipsWidget(QWidget *parent = 0);
    ~TLTipsWidget();
    void setText(const QString & text);
protected:
    void paintEvent(QPaintEvent *e);
    void showEvent(QShowEvent *e);
signals:

private slots:
    void onTimerStayOut();
    void onTimerCloseOut();//渐变后隐藏
private:
    QLabel* m_pLabel;
    QTimer * m_pTimer;
    QTimer * m_pCloseTimer;
    qreal m_dTransparent;
};

#endif // TLTIPWIDGET_H
