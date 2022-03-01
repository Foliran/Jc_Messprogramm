/********************************************************************************
** Form generated from reading UI file 'openfilewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENFILEWINDOW_H
#define UI_OPENFILEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_openfilewindow
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;

    void setupUi(QDialog *openfilewindow)
    {
        if (openfilewindow->objectName().isEmpty())
            openfilewindow->setObjectName(QString::fromUtf8("openfilewindow"));
        openfilewindow->resize(600, 200);
        pushButton = new QPushButton(openfilewindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(75, 40, 100, 30));
        pushButton_2 = new QPushButton(openfilewindow);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(240, 100, 150, 20));
        label = new QLabel(openfilewindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(200, 40, 300, 30));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        retranslateUi(openfilewindow);

        QMetaObject::connectSlotsByName(openfilewindow);
    } // setupUi

    void retranslateUi(QDialog *openfilewindow)
    {
        openfilewindow->setWindowTitle(QCoreApplication::translate("openfilewindow", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("openfilewindow", "Datei \303\266ffnen", nullptr));
        pushButton_2->setText(QCoreApplication::translate("openfilewindow", "Diagramm anzeigen", nullptr));
        label->setText(QCoreApplication::translate("openfilewindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class openfilewindow: public Ui_openfilewindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENFILEWINDOW_H
