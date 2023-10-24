#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    fwindow = new filewindow(this);
    fwindow->show();
}


void MainWindow::on_action_2_triggered()
{
    ewindow = new editwindow(this);
    ewindow->show();
}

void MainWindow::on_actionHelp_triggered()
{
    hwindow = new helpwindow(this);
    hwindow->show();
}

