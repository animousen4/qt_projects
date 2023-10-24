#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMenu>
#include <QAction>
#include <QObject>
#include <windowbloc.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    WindowBloc * wBloc = new WindowBloc;
    //QObject::connect(ui->menuEdit, SIGNAL(triggered()), wBloc, SLOT(onFilePressed()));
//    QMenuBar * menuBar = new QMenuBar(this);
//    QAction * fileAction = menuBar->addAction("File");
//    QAction * editAction = menuBar->addAction("Edit");



//    QObject::connect(fileAction, SIGNAL(triggered()), wBloc, SLOT(onFilePressed()));



}

MainWindow::~MainWindow()
{
    delete ui;
}

