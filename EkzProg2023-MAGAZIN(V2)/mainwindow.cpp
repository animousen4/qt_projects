#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <TableModels.h>
#include <QLabel>
#include <prettybloc.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(1400, 400);


    QVBoxLayout * bagLayout = new QVBoxLayout();
    QVBoxLayout * fruitLayout = new QVBoxLayout();

    bagLayout->addWidget(new PrettyBloc<Bag>(nullptr));
    fruitLayout->addWidget(new PrettyBloc<Fruit>(nullptr));

    ui->bagTab->setLayout(bagLayout);
    ui->fruitTab->setLayout(fruitLayout);



}
MainWindow::~MainWindow()
{
    delete ui;
}

