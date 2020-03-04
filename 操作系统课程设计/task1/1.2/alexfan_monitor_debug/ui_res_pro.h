/********************************************************************************
** Form generated from reading UI file 'res_pro.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RES_PRO_H
#define UI_RES_PRO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_res_pro
{
public:
    QLabel *CPU;
    QLabel *CPU_Monitor;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *res_pro)
    {
        if (res_pro->objectName().isEmpty())
            res_pro->setObjectName(QString::fromUtf8("res_pro"));
        res_pro->resize(523, 282);
        CPU = new QLabel(res_pro);
        CPU->setObjectName(QString::fromUtf8("CPU"));
        CPU->setGeometry(QRect(290, 80, 241, 31));
        QFont font;
        font.setPointSize(20);
        CPU->setFont(font);
        CPU_Monitor = new QLabel(res_pro);
        CPU_Monitor->setObjectName(QString::fromUtf8("CPU_Monitor"));
        CPU_Monitor->setGeometry(QRect(290, 160, 261, 41));
        CPU_Monitor->setFont(font);
        label = new QLabel(res_pro);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 80, 141, 31));
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);
        label_2 = new QLabel(res_pro);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 170, 131, 20));
        label_2->setFont(font1);
        label_3 = new QLabel(res_pro);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(490, 170, 67, 17));

        retranslateUi(res_pro);

        QMetaObject::connectSlotsByName(res_pro);
    } // setupUi

    void retranslateUi(QWidget *res_pro)
    {
        res_pro->setWindowTitle(QApplication::translate("res_pro", "Form", nullptr));
        CPU->setText(QApplication::translate("res_pro", "TextLabel", nullptr));
        CPU_Monitor->setText(QApplication::translate("res_pro", "TextLabel", nullptr));
        label->setText(QApplication::translate("res_pro", "CPU\347\233\221\350\247\206\345\231\250\350\277\233\347\250\213\345\217\267\357\274\232", nullptr));
        label_2->setText(QApplication::translate("res_pro", "CPU\350\265\204\346\272\220\345\210\251\347\224\250\347\216\207\357\274\232", nullptr));
        label_3->setText(QApplication::translate("res_pro", "%", nullptr));
    } // retranslateUi

};

namespace Ui {
    class res_pro: public Ui_res_pro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RES_PRO_H
