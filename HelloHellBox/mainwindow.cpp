#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString t1 = "Hello world";
    QString t2 = "Hello hell";

    QMessageBox * msgBox = new QMessageBox;
    msgBox->setWindowTitle("This is MessageBox");
    msgBox->setText("This is MessageBox");
    msgBox->setDefaultButton(QMessageBox::Ok);

    connect(msgBox->button(QMessageBox::Ok), &QPushButton::clicked, this, [this, msgBox, t2](){
        msgBox->close();
        QMessageBox * msg2 = new QMessageBox;
        msg2->setWindowTitle(t2);
        msg2->setText(t2);
        msg2->show();
    });
    msgBox->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

