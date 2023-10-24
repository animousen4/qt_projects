/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *enterExp_edit;
    QLabel *enterExp_lbl;
    QTextEdit *enterVar_edit;
    QLabel *enterVar_lbl;
    QLabel *example_lbl;
    QLabel *newExp_lbl;
    QTextBrowser *newExp_show;
    QLCDNumber *answer_lcd;
    QLabel *answer_lbl;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        enterExp_edit = new QLineEdit(centralwidget);
        enterExp_edit->setObjectName(QString::fromUtf8("enterExp_edit"));
        enterExp_edit->setGeometry(QRect(64, 126, 371, 31));
        enterExp_lbl = new QLabel(centralwidget);
        enterExp_lbl->setObjectName(QString::fromUtf8("enterExp_lbl"));
        enterExp_lbl->setGeometry(QRect(154, 86, 211, 21));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        enterExp_lbl->setFont(font);
        enterExp_lbl->setAlignment(Qt::AlignCenter);
        enterVar_edit = new QTextEdit(centralwidget);
        enterVar_edit->setObjectName(QString::fromUtf8("enterVar_edit"));
        enterVar_edit->setGeometry(QRect(494, 116, 231, 201));
        enterVar_lbl = new QLabel(centralwidget);
        enterVar_lbl->setObjectName(QString::fromUtf8("enterVar_lbl"));
        enterVar_lbl->setGeometry(QRect(504, 76, 211, 21));
        enterVar_lbl->setFont(font);
        enterVar_lbl->setAlignment(Qt::AlignCenter);
        example_lbl = new QLabel(centralwidget);
        example_lbl->setObjectName(QString::fromUtf8("example_lbl"));
        example_lbl->setGeometry(QRect(544, 326, 131, 31));
        QFont font1;
        font1.setPointSize(10);
        font1.setUnderline(true);
        example_lbl->setFont(font1);
        newExp_lbl = new QLabel(centralwidget);
        newExp_lbl->setObjectName(QString::fromUtf8("newExp_lbl"));
        newExp_lbl->setGeometry(QRect(154, 196, 211, 31));
        newExp_lbl->setFont(font);
        newExp_lbl->setAlignment(Qt::AlignCenter);
        newExp_show = new QTextBrowser(centralwidget);
        newExp_show->setObjectName(QString::fromUtf8("newExp_show"));
        newExp_show->setGeometry(QRect(64, 236, 371, 31));
        answer_lcd = new QLCDNumber(centralwidget);
        answer_lcd->setObjectName(QString::fromUtf8("answer_lcd"));
        answer_lcd->setGeometry(QRect(280, 490, 231, 61));
        answer_lbl = new QLabel(centralwidget);
        answer_lbl->setObjectName(QString::fromUtf8("answer_lbl"));
        answer_lbl->setGeometry(QRect(352, 420, 91, 41));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        answer_lbl->setFont(font2);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        enterExp_lbl->setText(QCoreApplication::translate("MainWindow", "enter your expression", nullptr));
        enterVar_lbl->setText(QCoreApplication::translate("MainWindow", "enter your variables", nullptr));
        example_lbl->setText(QCoreApplication::translate("MainWindow", "example : a = 4", nullptr));
        newExp_lbl->setText(QCoreApplication::translate("MainWindow", "correccted expression", nullptr));
        answer_lbl->setText(QCoreApplication::translate("MainWindow", "Answer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
