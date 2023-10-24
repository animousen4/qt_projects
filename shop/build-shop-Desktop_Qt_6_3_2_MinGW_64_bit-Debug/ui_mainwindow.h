/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *products_tab;
    QGridLayout *gridLayout;
    QTableView *secondSet_tbl;
    QPushButton *sortSets_btn;
    QTableView *firstSet_tbl;
    QLabel *mergedSet_lbl;
    QTableView *mergedSet_tbl;
    QLabel *secondSet_lbl;
    QLabel *firstSet_lbl;
    QPushButton *mergeSets_btn;
    QWidget *bags_tab;
    QGridLayout *gridLayout_2;
    QLabel *firstBag_lbl;
    QLabel *secondBag_lbl;
    QLabel *mergedBags_lbl;
    QTableView *firstBag_tbl;
    QTableView *secondBag_tbl;
    QTableView *mergedBags_tbl;
    QPushButton *sortBags_btn;
    QPushButton *mergeBags_btn;
    QWidget *enterWidget;
    QSplitter *enterPart;
    QLabel *enterProd1_lbl;
    QLineEdit *prod1_edit;
    QLabel *enterProd2_lbl;
    QLineEdit *prod2_edit;
    QLabel *enterBag1_lbl;
    QLineEdit *bag1_edit;
    QLabel *enterBag2_lbl;
    QLineEdit *bag2_edit;
    QLabel *enterMProd_lbl;
    QLineEdit *mergedProd_edit;
    QLabel *enterMBags_lbl;
    QLineEdit *mergedBags_edit;
    QLabel *enterNames1_lbl;
    QPushButton *findObject_btn;
    QLabel *enterNames2_lbl;
    QPushButton *openFiles_btn;
    QLineEdit *findObject_edit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(954, 705);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setPointSize(13);
        font.setBold(true);
        tabWidget->setFont(font);
        products_tab = new QWidget();
        products_tab->setObjectName(QString::fromUtf8("products_tab"));
        gridLayout = new QGridLayout(products_tab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        secondSet_tbl = new QTableView(products_tab);
        secondSet_tbl->setObjectName(QString::fromUtf8("secondSet_tbl"));
        secondSet_tbl->setMaximumSize(QSize(550, 16777215));

        gridLayout->addWidget(secondSet_tbl, 1, 1, 1, 1);

        sortSets_btn = new QPushButton(products_tab);
        sortSets_btn->setObjectName(QString::fromUtf8("sortSets_btn"));
        QFont font1;
        font1.setBold(false);
        sortSets_btn->setFont(font1);

        gridLayout->addWidget(sortSets_btn, 2, 0, 1, 1);

        firstSet_tbl = new QTableView(products_tab);
        firstSet_tbl->setObjectName(QString::fromUtf8("firstSet_tbl"));
        firstSet_tbl->setMaximumSize(QSize(550, 16777215));
        firstSet_tbl->horizontalHeader()->setStretchLastSection(false);

        gridLayout->addWidget(firstSet_tbl, 1, 0, 1, 1);

        mergedSet_lbl = new QLabel(products_tab);
        mergedSet_lbl->setObjectName(QString::fromUtf8("mergedSet_lbl"));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(false);
        mergedSet_lbl->setFont(font2);
        mergedSet_lbl->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(mergedSet_lbl, 0, 2, 1, 2);

        mergedSet_tbl = new QTableView(products_tab);
        mergedSet_tbl->setObjectName(QString::fromUtf8("mergedSet_tbl"));

        gridLayout->addWidget(mergedSet_tbl, 1, 2, 1, 2);

        secondSet_lbl = new QLabel(products_tab);
        secondSet_lbl->setObjectName(QString::fromUtf8("secondSet_lbl"));
        secondSet_lbl->setFont(font2);
        secondSet_lbl->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(secondSet_lbl, 0, 1, 1, 1);

        firstSet_lbl = new QLabel(products_tab);
        firstSet_lbl->setObjectName(QString::fromUtf8("firstSet_lbl"));
        firstSet_lbl->setFont(font2);
        firstSet_lbl->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(firstSet_lbl, 0, 0, 1, 1);

        mergeSets_btn = new QPushButton(products_tab);
        mergeSets_btn->setObjectName(QString::fromUtf8("mergeSets_btn"));
        mergeSets_btn->setMinimumSize(QSize(0, 36));
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(false);
        mergeSets_btn->setFont(font3);

        gridLayout->addWidget(mergeSets_btn, 2, 2, 1, 2);

        tabWidget->addTab(products_tab, QString());
        bags_tab = new QWidget();
        bags_tab->setObjectName(QString::fromUtf8("bags_tab"));
        gridLayout_2 = new QGridLayout(bags_tab);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        firstBag_lbl = new QLabel(bags_tab);
        firstBag_lbl->setObjectName(QString::fromUtf8("firstBag_lbl"));
        firstBag_lbl->setFont(font2);
        firstBag_lbl->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(firstBag_lbl, 0, 0, 1, 1);

        secondBag_lbl = new QLabel(bags_tab);
        secondBag_lbl->setObjectName(QString::fromUtf8("secondBag_lbl"));
        secondBag_lbl->setFont(font2);
        secondBag_lbl->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(secondBag_lbl, 0, 1, 1, 1);

        mergedBags_lbl = new QLabel(bags_tab);
        mergedBags_lbl->setObjectName(QString::fromUtf8("mergedBags_lbl"));
        mergedBags_lbl->setFont(font2);
        mergedBags_lbl->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(mergedBags_lbl, 0, 2, 1, 2);

        firstBag_tbl = new QTableView(bags_tab);
        firstBag_tbl->setObjectName(QString::fromUtf8("firstBag_tbl"));
        firstBag_tbl->setMaximumSize(QSize(550, 16777215));

        gridLayout_2->addWidget(firstBag_tbl, 1, 0, 1, 1);

        secondBag_tbl = new QTableView(bags_tab);
        secondBag_tbl->setObjectName(QString::fromUtf8("secondBag_tbl"));
        secondBag_tbl->setMaximumSize(QSize(550, 16777215));

        gridLayout_2->addWidget(secondBag_tbl, 1, 1, 1, 1);

        mergedBags_tbl = new QTableView(bags_tab);
        mergedBags_tbl->setObjectName(QString::fromUtf8("mergedBags_tbl"));

        gridLayout_2->addWidget(mergedBags_tbl, 1, 2, 1, 2);

        sortBags_btn = new QPushButton(bags_tab);
        sortBags_btn->setObjectName(QString::fromUtf8("sortBags_btn"));
        sortBags_btn->setFont(font1);

        gridLayout_2->addWidget(sortBags_btn, 2, 0, 1, 1);

        mergeBags_btn = new QPushButton(bags_tab);
        mergeBags_btn->setObjectName(QString::fromUtf8("mergeBags_btn"));
        mergeBags_btn->setMinimumSize(QSize(0, 36));
        mergeBags_btn->setFont(font3);

        gridLayout_2->addWidget(mergeBags_btn, 2, 2, 1, 2);

        tabWidget->addTab(bags_tab, QString());

        horizontalLayout->addWidget(tabWidget);

        enterWidget = new QWidget(centralwidget);
        enterWidget->setObjectName(QString::fromUtf8("enterWidget"));
        enterWidget->setMinimumSize(QSize(200, 0));
        enterPart = new QSplitter(enterWidget);
        enterPart->setObjectName(QString::fromUtf8("enterPart"));
        enterPart->setGeometry(QRect(19, 156, 151, 321));
        enterPart->setOrientation(Qt::Vertical);
        enterProd1_lbl = new QLabel(enterPart);
        enterProd1_lbl->setObjectName(QString::fromUtf8("enterProd1_lbl"));
        QFont font4;
        font4.setPointSize(11);
        enterProd1_lbl->setFont(font4);
        enterPart->addWidget(enterProd1_lbl);
        prod1_edit = new QLineEdit(enterPart);
        prod1_edit->setObjectName(QString::fromUtf8("prod1_edit"));
        enterPart->addWidget(prod1_edit);
        enterProd2_lbl = new QLabel(enterPart);
        enterProd2_lbl->setObjectName(QString::fromUtf8("enterProd2_lbl"));
        QFont font5;
        font5.setPointSize(10);
        enterProd2_lbl->setFont(font5);
        enterPart->addWidget(enterProd2_lbl);
        prod2_edit = new QLineEdit(enterPart);
        prod2_edit->setObjectName(QString::fromUtf8("prod2_edit"));
        enterPart->addWidget(prod2_edit);
        enterBag1_lbl = new QLabel(enterPart);
        enterBag1_lbl->setObjectName(QString::fromUtf8("enterBag1_lbl"));
        enterBag1_lbl->setFont(font4);
        enterPart->addWidget(enterBag1_lbl);
        bag1_edit = new QLineEdit(enterPart);
        bag1_edit->setObjectName(QString::fromUtf8("bag1_edit"));
        enterPart->addWidget(bag1_edit);
        enterBag2_lbl = new QLabel(enterPart);
        enterBag2_lbl->setObjectName(QString::fromUtf8("enterBag2_lbl"));
        enterBag2_lbl->setFont(font5);
        enterPart->addWidget(enterBag2_lbl);
        bag2_edit = new QLineEdit(enterPart);
        bag2_edit->setObjectName(QString::fromUtf8("bag2_edit"));
        enterPart->addWidget(bag2_edit);
        enterMProd_lbl = new QLabel(enterPart);
        enterMProd_lbl->setObjectName(QString::fromUtf8("enterMProd_lbl"));
        enterMProd_lbl->setFont(font4);
        enterPart->addWidget(enterMProd_lbl);
        mergedProd_edit = new QLineEdit(enterPart);
        mergedProd_edit->setObjectName(QString::fromUtf8("mergedProd_edit"));
        enterPart->addWidget(mergedProd_edit);
        enterMBags_lbl = new QLabel(enterPart);
        enterMBags_lbl->setObjectName(QString::fromUtf8("enterMBags_lbl"));
        enterMBags_lbl->setFont(font5);
        enterPart->addWidget(enterMBags_lbl);
        mergedBags_edit = new QLineEdit(enterPart);
        mergedBags_edit->setObjectName(QString::fromUtf8("mergedBags_edit"));
        enterPart->addWidget(mergedBags_edit);
        enterNames1_lbl = new QLabel(enterWidget);
        enterNames1_lbl->setObjectName(QString::fromUtf8("enterNames1_lbl"));
        enterNames1_lbl->setGeometry(QRect(16, 66, 161, 41));
        QFont font6;
        font6.setPointSize(12);
        enterNames1_lbl->setFont(font6);
        findObject_btn = new QPushButton(enterWidget);
        findObject_btn->setObjectName(QString::fromUtf8("findObject_btn"));
        findObject_btn->setGeometry(QRect(53, 600, 93, 28));
        QFont font7;
        font7.setBold(true);
        findObject_btn->setFont(font7);
        enterNames2_lbl = new QLabel(enterWidget);
        enterNames2_lbl->setObjectName(QString::fromUtf8("enterNames2_lbl"));
        enterNames2_lbl->setGeometry(QRect(40, 98, 120, 31));
        enterNames2_lbl->setFont(font6);
        openFiles_btn = new QPushButton(enterWidget);
        openFiles_btn->setObjectName(QString::fromUtf8("openFiles_btn"));
        openFiles_btn->setGeometry(QRect(40, 490, 101, 31));
        QFont font8;
        font8.setPointSize(10);
        font8.setBold(true);
        openFiles_btn->setFont(font8);
        findObject_edit = new QLineEdit(enterWidget);
        findObject_edit->setObjectName(QString::fromUtf8("findObject_edit"));
        findObject_edit->setGeometry(QRect(20, 560, 161, 31));

        horizontalLayout->addWidget(enterWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        sortSets_btn->setText(QCoreApplication::translate("MainWindow", "sort all products tables", nullptr));
        mergedSet_lbl->setText(QCoreApplication::translate("MainWindow", "merged", nullptr));
        secondSet_lbl->setText(QCoreApplication::translate("MainWindow", "2nd set", nullptr));
        firstSet_lbl->setText(QCoreApplication::translate("MainWindow", "1st set", nullptr));
        mergeSets_btn->setText(QCoreApplication::translate("MainWindow", "merge and sort sets", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(products_tab), QCoreApplication::translate("MainWindow", "Products", nullptr));
        firstBag_lbl->setText(QCoreApplication::translate("MainWindow", "1st bag", nullptr));
        secondBag_lbl->setText(QCoreApplication::translate("MainWindow", "2nd bag", nullptr));
        mergedBags_lbl->setText(QCoreApplication::translate("MainWindow", "merged", nullptr));
        sortBags_btn->setText(QCoreApplication::translate("MainWindow", "sort all bags", nullptr));
        mergeBags_btn->setText(QCoreApplication::translate("MainWindow", "merge and sort bags", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(bags_tab), QCoreApplication::translate("MainWindow", "Bags", nullptr));
        enterProd1_lbl->setText(QCoreApplication::translate("MainWindow", "products, 1st set:", nullptr));
        prod1_edit->setText(QCoreApplication::translate("MainWindow", "products1.txt", nullptr));
        enterProd2_lbl->setText(QCoreApplication::translate("MainWindow", "products, 2nd set:", nullptr));
        prod2_edit->setText(QCoreApplication::translate("MainWindow", "products2.txt", nullptr));
        enterBag1_lbl->setText(QCoreApplication::translate("MainWindow", "1st bag:", nullptr));
        bag1_edit->setText(QCoreApplication::translate("MainWindow", "bag1.txt", nullptr));
        enterBag2_lbl->setText(QCoreApplication::translate("MainWindow", "2nd bag:", nullptr));
        bag2_edit->setText(QCoreApplication::translate("MainWindow", "bag2.txt", nullptr));
        enterMProd_lbl->setText(QCoreApplication::translate("MainWindow", "merged products:", nullptr));
        mergedProd_edit->setText(QCoreApplication::translate("MainWindow", "mergedProducts.txt", nullptr));
        enterMBags_lbl->setText(QCoreApplication::translate("MainWindow", "merged bags:", nullptr));
        mergedBags_edit->setText(QCoreApplication::translate("MainWindow", "mergedBags.txt", nullptr));
        enterNames1_lbl->setText(QCoreApplication::translate("MainWindow", "enter the names", nullptr));
        findObject_btn->setText(QCoreApplication::translate("MainWindow", "find item", nullptr));
        enterNames2_lbl->setText(QCoreApplication::translate("MainWindow", "of your files:", nullptr));
        openFiles_btn->setText(QCoreApplication::translate("MainWindow", "open files", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
