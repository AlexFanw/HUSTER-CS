/********************************************************************************
** Form generated from reading UI file 'res_mem.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RES_MEM_H
#define UI_RES_MEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_res_mem
{
public:
    QLabel *label_2;
    QLabel *Mem;
    QLabel *label;
    QLabel *Mem_Free;
    QLabel *label_3;
    QLabel *Mem_Monitor;

    void setupUi(QWidget *res_mem)
    {
        if (res_mem->objectName().isEmpty())
            res_mem->setObjectName(QString::fromUtf8("res_mem"));
        res_mem->resize(523, 282);
        label_2 = new QLabel(res_mem);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(140, 140, 131, 31));
        Mem = new QLabel(res_mem);
        Mem->setObjectName(QString::fromUtf8("Mem"));
        Mem->setGeometry(QRect(270, 80, 181, 31));
        QFont font;
        font.setPointSize(20);
        Mem->setFont(font);
        label = new QLabel(res_mem);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 80, 151, 21));
        QFont font1;
        font1.setPointSize(13);
        label->setFont(font1);
        Mem_Free = new QLabel(res_mem);
        Mem_Free->setObjectName(QString::fromUtf8("Mem_Free"));
        Mem_Free->setGeometry(QRect(270, 190, 191, 31));
        Mem_Free->setFont(font);
        label_3 = new QLabel(res_mem);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(140, 200, 101, 21));
        Mem_Monitor = new QLabel(res_mem);
        Mem_Monitor->setObjectName(QString::fromUtf8("Mem_Monitor"));
        Mem_Monitor->setGeometry(QRect(270, 140, 181, 31));
        Mem_Monitor->setFont(font);

        retranslateUi(res_mem);

        QMetaObject::connectSlotsByName(res_mem);
    } // setupUi

    void retranslateUi(QWidget *res_mem)
    {
        res_mem->setWindowTitle(QApplication::translate("res_mem", "Form", nullptr));
        label_2->setText(QApplication::translate("res_mem", "\345\206\205\345\255\230\346\200\273\351\207\217\357\274\232", nullptr));
        Mem->setText(QApplication::translate("res_mem", "Mem", nullptr));
        label->setText(QApplication::translate("res_mem", "\347\233\221\350\247\206\345\231\250\350\277\233\347\250\213\345\217\267\357\274\232", nullptr));
        Mem_Free->setText(QApplication::translate("res_mem", "Mem_Free", nullptr));
        label_3->setText(QApplication::translate("res_mem", "\345\206\205\345\255\230\345\211\251\344\275\231\351\207\217\357\274\232", nullptr));
        Mem_Monitor->setText(QApplication::translate("res_mem", "Mem_Monitor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class res_mem: public Ui_res_mem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RES_MEM_H
