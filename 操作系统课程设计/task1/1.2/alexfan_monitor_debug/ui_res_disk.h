/********************************************************************************
** Form generated from reading UI file 'res_disk.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RES_DISK_H
#define UI_RES_DISK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_res_disk
{
public:
    QLabel *Disk_Monitor;
    QLabel *Disk;
    QLabel *label;
    QLabel *label_2;
    QLabel *Disk_Free;
    QLabel *label_3;

    void setupUi(QWidget *res_disk)
    {
        if (res_disk->objectName().isEmpty())
            res_disk->setObjectName(QString::fromUtf8("res_disk"));
        res_disk->resize(523, 282);
        Disk_Monitor = new QLabel(res_disk);
        Disk_Monitor->setObjectName(QString::fromUtf8("Disk_Monitor"));
        Disk_Monitor->setGeometry(QRect(270, 130, 181, 31));
        QFont font;
        font.setPointSize(20);
        Disk_Monitor->setFont(font);
        Disk = new QLabel(res_disk);
        Disk->setObjectName(QString::fromUtf8("Disk"));
        Disk->setGeometry(QRect(270, 70, 181, 31));
        Disk->setFont(font);
        label = new QLabel(res_disk);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 70, 151, 21));
        QFont font1;
        font1.setPointSize(13);
        label->setFont(font1);
        label_2 = new QLabel(res_disk);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(140, 130, 131, 31));
        Disk_Free = new QLabel(res_disk);
        Disk_Free->setObjectName(QString::fromUtf8("Disk_Free"));
        Disk_Free->setGeometry(QRect(270, 180, 191, 31));
        Disk_Free->setFont(font);
        label_3 = new QLabel(res_disk);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(140, 190, 101, 21));

        retranslateUi(res_disk);

        QMetaObject::connectSlotsByName(res_disk);
    } // setupUi

    void retranslateUi(QWidget *res_disk)
    {
        res_disk->setWindowTitle(QApplication::translate("res_disk", "Form", nullptr));
        Disk_Monitor->setText(QApplication::translate("res_disk", "Disk_Monitor", nullptr));
        Disk->setText(QApplication::translate("res_disk", "Disk", nullptr));
        label->setText(QApplication::translate("res_disk", "\347\233\221\350\247\206\345\231\250\350\277\233\347\250\213\345\217\267\357\274\232", nullptr));
        label_2->setText(QApplication::translate("res_disk", "\347\243\201\347\233\230\344\275\277\347\224\250\351\207\217\357\274\232", nullptr));
        Disk_Free->setText(QApplication::translate("res_disk", "Disk_Free", nullptr));
        label_3->setText(QApplication::translate("res_disk", "\347\243\201\347\233\230\345\211\251\344\275\231\351\207\217\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class res_disk: public Ui_res_disk {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RES_DISK_H
