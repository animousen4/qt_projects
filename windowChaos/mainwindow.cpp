#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QGuiApplication>
#include <QScreen>
#include <QPushButton>
#include <QRandomGenerator>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMessageBox * msgBox = new QMessageBox;
    msgBox->setWindowTitle("This is MessageBox");
    msgBox->setText("This is MessageBox");
    msgBox->setDefaultButton(QMessageBox::Ok);
    msgBox->move(0,0);
    msgBox->show();

    QTimer * timer = new QTimer();
    timer->setInterval(250);

    double ySize = QGuiApplication::primaryScreen()->geometry().height();
    double xSize = QGuiApplication::primaryScreen()->geometry().width();

    QRandomGenerator * r = new QRandomGenerator;
    connect(msgBox->button(QMessageBox::Ok), &QPushButton::clicked, this, [this, msgBox](){
        msgBox->close();
        this->close();
    });
    connect(timer, &QTimer::timeout, this, [msgBox, r, xSize, ySize](){
        msgBox->move(r->bounded(0, (int)xSize + 1), r->bounded(0, (int)ySize + 1));
    });
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

