/********************************************************************************
** Form generated from reading UI file 'findinfo.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDINFO_H
#define UI_FINDINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_FindInfo
{
public:
    QPushButton *pushButton;
    QTextBrowser *infoBrowser;

    void setupUi(QDialog *FindInfo)
    {
        if (FindInfo->objectName().isEmpty())
            FindInfo->setObjectName(QString::fromUtf8("FindInfo"));
        FindInfo->resize(400, 300);
        pushButton = new QPushButton(FindInfo);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(150, 240, 93, 28));
        infoBrowser = new QTextBrowser(FindInfo);
        infoBrowser->setObjectName(QString::fromUtf8("infoBrowser"));
        infoBrowser->setGeometry(QRect(10, 70, 381, 101));
        infoBrowser->setFrameShape(QFrame::NoFrame);
        infoBrowser->setFrameShadow(QFrame::Plain);

        retranslateUi(FindInfo);

        QMetaObject::connectSlotsByName(FindInfo);
    } // setupUi

    void retranslateUi(QDialog *FindInfo)
    {
        FindInfo->setWindowTitle(QCoreApplication::translate("FindInfo", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("FindInfo", "ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindInfo: public Ui_FindInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDINFO_H
