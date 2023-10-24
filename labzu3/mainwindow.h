#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMouseEvent>
#include "ui_mainwindow.h"
#include <QCursor>
#include <QTimer>
#include <QtMath>
#include <QList>
#include <QPropertyAnimation>
#include <QAudioOutput>
#include <QMediaPlayer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr): QMainWindow(parent), ui(new Ui::MainWindow) {
        ui->setupUi(this);
        this->setCursor(QCursor(QPixmap("mat/bit.png").scaled(40,40)));
        this->centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
        setMouseTracking(true);

        lives = images.length() - 1;
        vx = 0;
        vy = 0;
        watching = false;
        mx = QCursor::pos().x();
        my = QCursor::pos().y();

        timer = new QTimer(this);
        timer->setInterval(10);
        connect(timer, &QTimer::timeout, [this]() {
            watching = d(x,y,mx,my) < watchR;

            if (isOut()) {
                double cx = (double)size().width() / 2;
                double cy = (double)size().height() / 2;

                double tx = (cx - x)/1.7;
                double ty = (cy - y)/1.7;

                vx = 0;
                vy = 0;

                x = cx + tx;
                y = cy + ty;


            } else {

                if (watching) {

                    double mult = watchR/d(x,y,mx,my) - 1;

                    double tx = (x - mx)*mult;
                    double ty = (y - my)*mult;

                    vx = tx;
                    vy = ty;

                } else {
                    vx = 0;
                    vy = 0;
                }

                if (d(vx,vy, 0,0) > sp) {
                    double tk = sp/d(vx,vy, 0,0);
                    vx = vx*tk;
                    vy = vy*tk;
                }

            }

            x = x + vx*timer->interval()/100;
            y = y + vy*timer->interval()/100;


            ch->move(x - (double)ch->size().width() / 2, y - (double)ch->size().height() / 2);

            qDebug() << isOut();
        });

        x = (double)size().width() / 2;
        y = (double)size().height() / 2;


        if (isOut() && !watching) {

        }

        ch = new QLabel(this);
        kat = new QLabel(this);
        ch->setPixmap(QPixmap(images[lives]).scaled(110,70, Qt::KeepAspectRatio));
        ch->setFixedSize(ch->pixmap().size());

        ch->move(x - (double)ch->size().width() / 2, y - (double)ch->size().height() / 2);

        timer->start();
    }
    ~MainWindow() {
        delete ui;
    }


protected:
    void mouseMoveEvent(QMouseEvent *event) override
    {
        QPoint pos = event->pos(); // Get the position of the mouse cursor
        qDebug() << "Mouse moved to: " << pos;

        mx = pos.x();
        my = pos.y();
    }

    void mousePressEvent(QMouseEvent* event) override {
        if (lives != 0)
            if (ch->geometry().contains(event->pos())) {
               lives--;
               if (lives == 0) {
                   ch->setPixmap(QPixmap(images[0]).scaled(110,70, Qt::KeepAspectRatio));
                   timer->stop();

                   kat->setPixmap(QPixmap(katImg).scaled(200,70, Qt::KeepAspectRatio));

                   kat->setFixedSize(kat->pixmap().size());
                   kat->move(-kat->pixmap().size().width(), size().height()/2-kat->pixmap().size().height());


                   QMediaPlayer * player = new QMediaPlayer();
                   QAudioOutput * audioOutput = new QAudioOutput;
                   player->setAudioOutput(audioOutput);
                   audioOutput->setVolume(0.30);

                   player->setSource(QUrl(sadSong));
                   player->play();

                   QPropertyAnimation * animation = new QPropertyAnimation(kat, "pos");
                   animation->setDuration(6000); // 2 seconds
                   animation->setStartValue(kat->pos());
                   animation->setEndValue(QPoint(x,y));

                   connect(animation, &QPropertyAnimation::finished, [this](){
                       QPoint dest = QPoint(-kat->pixmap().size().width(), size().height()/2-kat->pixmap().size().height());
                       QPropertyAnimation * animation2 = new QPropertyAnimation(kat, "pos");

                       ch->hide();
                       animation2->setDuration(6000);
                       animation2->setStartValue(QPoint(x,y));
                       animation2->setEndValue(dest);

                       animation2->start();
                   });

                   animation->start();
                   return;
               } else {
                    ch->setPixmap(QPixmap(images[lives]).scaled(110,70, Qt::KeepAspectRatio));
               }
            }
    }


private:
    Ui::MainWindow * ui;
    double x;
    double y;

    // радиус просмотра
    double watchR = 180;

    // макс скорость
    double sp = 55;

    double mx;
    double my;

    double vx;
    double vy;

    bool watching;

    int lives;


    QTimer * timer;
    QLabel * ch;
    QLabel * kat;
    QString sadSong = "mat/ded.mp3";
    QString katImg = "mat/k.png";
    QList<QString> images = {"mat/44.jpg", "mat/33.jpg", "mat/22.jpg", "mat/11.jpg"};

    double d(double x1, double y1, double x2, double y2) {
        return qSqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    }

    bool isOut() {
        int bx = size().width();
        int by = size().height();
        return (x < 0 || y < 0 || x > bx || y > by);
    }



};
#endif // MAINWINDOW_H
