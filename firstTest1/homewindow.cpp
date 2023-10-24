#include "homewindow.h"
#include "./ui_homewindow.h"
#include <QApplication>
#include <QScreen>
HomeWindow::HomeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomeWindow)
{
    ui->setupUi(this);
    QRect scrSize = QApplication::screens()[0]->geometry();
    k = scrSize.width() / scrSize.height();
    //timer = new QTimer();
    //connect(timer, SIGNAL(timeout()), this, SLOT(shotTimer()));
    //timer->start(1000);
}
// each 1 sec
void HomeWindow::shotTimer() {

    this->move(QPoint(this->pos().x() + 1, (this->pos().x() + 1)*k));
}
HomeWindow::~HomeWindow()
{
    delete ui;
}

