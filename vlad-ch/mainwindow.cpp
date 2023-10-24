
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>

void delay()
{
    QTime dieTime= QTime::currentTime().addMSecs(150);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    count = 0;
    ui->setupUi(this);
    ui->car->hide();
    ui->pushButton->setEnabled(false);
    QCursor cursor = QCursor(QPixmap(":/pictures/bita.png"), 0, 0);
    this->setCursor(cursor);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    player = new QMediaPlayer();
    QAudioOutput * audioOutput = new QAudioOutput;
    audioOutput->setVolume(100);
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/music/hit.mp3"));
    player->play();
    delay();
    if (count == 2) {
        count = count + 1;
        ui->car->show();
        ui->pushButton->setEnabled(false);
        ui->pushButton->setIcon(QIcon(":/pictures/zubovich3.jpg"));
        player = new QMediaPlayer();
        QAudioOutput * audioOutput = new QAudioOutput;
        audioOutput->setVolume(100);
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl("qrc:/music/death.mp3"));
        player->play();
        QRect Pos = ui->pushButton->geometry();
        short X, Y;
        X = 700;
        Y = Pos.y();
        while (X > -200) {
            ui->car->move(X, Y);
            if (X - Pos.x() < 5) ui->pushButton->hide();
            X = X - 5;
            delay();
        }
        player->stop();
        ui->car->hide();
    }
    else {
        count = count + 1;
        if (count == 1) ui->pushButton->setIcon(QIcon(":/pictures/zubovich1.jpg"));
        else if (count == 2) ui->pushButton->setIcon(QIcon(":/pictures/zubovich2.jpg"));
    }
}


void MainWindow::on_Start_clicked()
{
    ui->pushButton->setEnabled(true);
    ui->Start->setEnabled(false);
    ui->Start->hide();
    QRect PosZu = ui->pushButton->geometry();
    QPoint PosMouse; int XM1, YM1, XM2 = 0, YM2 = 0; int moveX = 0, moveY = 0;
    PosMouse = QCursor::pos();
    XM1 = PosMouse.x();
    YM1 = PosMouse.y();
    int XZ = PosZu.x();
    int YZ = PosZu.y();
    while (count != 3){
        PosMouse = QCursor::pos();
        XM2 = PosMouse.x();
        YM2 = PosMouse.y();
        moveX = XM2 - XM1;
        moveY = YM2 - YM1;
        if (XZ > 650) {
            moveX = moveX - 200;
        }
        else if (XZ < 50) {
            moveX = moveX + 200;
        }
        else if (YZ > 500) {
            moveY = moveY - 200;
        }
        else if (YZ < 50) {
            moveY = moveY + 200;
        }
        XZ = XZ + moveX;
        YZ = YZ + moveY;
        animationGroup = new QSequentialAnimationGroup(this);
        QPropertyAnimation* Move = new QPropertyAnimation(ui->pushButton, "geometry");
        Move->setDuration(150);
        Move->setStartValue(ui->pushButton->geometry());
        Move->setEndValue(ui->pushButton->geometry().translated(moveX, moveY));
        animationGroup->addAnimation(Move);
        animationGroup->start();
        delay();
        XM1 = XM2;
        YM1 = YM2;
    }
    animationGroup->stop();
    animationGroup->clear();
}

