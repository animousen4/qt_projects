#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QGuiApplication>
#include <QScreen>
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString t1 = "Hello world";
    QString t2 = "Hello hell";

    QMessageBox * msgBox = new QMessageBox;
    msgBox->setWindowTitle(t1);
    msgBox->setText(t1);
    msgBox->setDefaultButton(QMessageBox::Ok);
    msgBox->show();

    connect(msgBox->button(QMessageBox::Ok), &QPushButton::clicked, this, [this, msgBox, t2](){
        msgBox->close();
        QMessageBox * msg2 = new QMessageBox;
        msg2->setWindowTitle(t2);
        msg2->setText(t2);
        msg2->show();
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

