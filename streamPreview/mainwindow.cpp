#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDataStream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file("f.txt");
    QDataStream s(&file);

    file.open(QFile::ReadOnly);

    s << "AAAAAA" << 121.04 << "MKD" << 1;

    file.close();


}

MainWindow::~MainWindow()
{
    delete ui;
}

