#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QTimer>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), mass(100), nuge(2050)
{
    ui->setupUi(this);

    this->centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->setMouseTracking(true);
    this->setFixedSize(size());

    cursorF = new Vector(0,0);
    resistF = new Vector(0,0);
    pushF = new Vector(0,0);

    timer = new QTimer();
    timer->setInterval(10);
    timer->start();

    connect(timer, &QTimer::timeout, this,  &MainWindow::update);

    this->setGeometry(200, 50, 1500, 950);

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    QCursor mainCursor = QCursor(QPixmap("resources/beat3.png"), 0, 0);
    this->setCursor(mainCursor);

    ded = new QLabel(this);

    targetPosition = new Vector(150, 150);
    velocity = new Vector(0, 0);
    acceleration = new Vector(0, 0);
    mousePosition = new Vector(QCursor::pos().x(),QCursor::pos().y());
    radius = 250;

    ded->setGeometry(150, 150, 100, 100);

    QPixmap pm = QPixmap("resources/ded3.jpg").scaled(QSize(100, 100), Qt::KeepAspectRatio);
    ded->setScaledContents(true);
    ded->setPixmap(pm);
    ded->setFixedSize(pm.size().width(), pm.size().height());

    this->ded->setAttribute(Qt::WA_TransparentForMouseEvents);
}

void MainWindow::paintEvent(QPaintEvent *event) {

    //qDebug() << "repainting";

    QPainter painter(this);
    QPen pen(Qt::black, 2, Qt::SolidLine);
    painter.setPen(pen);
    QPen pen2(Qt::red, 2, Qt::SolidLine);
    painter.drawLine(targetPosition->getCoordinates().first, targetPosition->getCoordinates().second, (*targetPosition + *velocity).getCoordinates().first, (*targetPosition + *velocity).getCoordinates().second);
    painter.setPen(pen2);

    painter.drawLine(targetPosition->getCoordinates().first, targetPosition->getCoordinates().second, (*targetPosition + *acceleration).getCoordinates().first, (*targetPosition + *acceleration).getCoordinates().second);
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {

    mousePosition->setCoordinates((double)event->pos().x(), (double)event->pos().y());

    //qDebug() << mousePosition->getCoordinates().first << " " << mousePosition->getCoordinates().second;

    double distance = mousePosition->distance(targetPosition);

    //qDebug() << distance;

    if (distance <= radius) {

        //qDebug() << "triggered";

        double k = radius / distance;
        Vector vectorClosestInfluence = *targetPosition - *mousePosition;
        Vector radiusVector = vectorClosestInfluence*k;
        cursorF = new Vector(radiusVector - vectorClosestInfluence);
        *cursorF = *cursorF * 300;

        //qDebug() << cursorF->module();
    }
    else {
        //qDebug() << "out of range";
        cursorF = new Vector(0, 0);

    }

    return;
}


void MainWindow::update() {

    double delta = (double) timer->interval()/1000;

    //qDebug() << "VEL: " <<  velocity->module() << "\t" << "ACC: " << acceleration->module() << "\t" << "CURSOR: " <<cursorF->module() << "\t" << "RESIST: " <<resistF->module() << "\t" << "PUSH: " <<pushF->module();

    if (velocity->module() < 1.6) {
        velocity->setCoordinates(0,0);
        resistF->setCoordinates(0,0);
    }
        else
            *resistF = ( *velocity * (-1) * (1.0 / velocity->module()) * nuge * mass * 0.1);

    Vector result = (*cursorF + *resistF) + *pushF;

    *acceleration = result * (1.0 / mass);

    qDebug() << acceleration->module();
    //qDebug() << acceleration->getCoordinates().first << " " << acceleration->getCoordinates().second;

    *velocity = *velocity + *acceleration * delta;

    if (velocity->module() > maxVelocity)
        *velocity = *velocity * (1.0 / velocity->module()) * maxVelocity;

    *targetPosition = *targetPosition + (*velocity * delta);

    ded->move(targetPosition->getCoordinates().first, targetPosition->getCoordinates().second);

    //qDebug() << velocity->module();
    //qDebug() << targetPosition->getCoordinates().first << " " << targetPosition->getCoordinates().second << endl;

    repaint();

}

MainWindow::~MainWindow()
{
    delete ui;
}

