#include "homewindow.h"
#include "ui_homewindow.h"
#include "circletable.h"
#include <QLabel>
HomeWindow::HomeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomeWindow)
{
    ui->setupUi(this);
    CircleTable * circleTable = new CircleTable;

    circleTable->addItem(new QLabel("1"));
    circleTable->addItem(new QLabel("2"));
    circleTable->addItem(new QLabel("3"));

    circleTable->move(200, 200);
    circleTable->show();


}

HomeWindow::~HomeWindow()
{
    delete ui;
}

