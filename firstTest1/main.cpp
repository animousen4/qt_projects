#include "homewindow.h"

#include <QApplication>
#include <QtWidgets>
#include <random>

double random_double() {
    // Seed the random number generator with the current time
    return (float)rand() / (float)RAND_MAX;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bool useRandom = false;

    QMessageBox* msgBox = new QMessageBox();
    double k;
    QRect scrSize = QApplication::screens()[0]->geometry();

    int x = scrSize.width();
    int y = scrSize.height();

    int delay = 1;

    k = (double)y / x;

    QTimer* timer = new QTimer();
    timer->callOnTimeout([=](){
        if (useRandom) {
            msgBox->move(QPoint(x*random_double(), y*random_double()));
        }
        else {
            msgBox->move(QPoint(msgBox->pos().x() + 1, (msgBox->pos().x() + 1)*k));
            if (msgBox->pos().x() == x)
                timer->stop();
        }
    });

    timer->start(delay);
    msgBox->move(0, 0);
    msgBox->setWindowTitle("Hello world!");
    msgBox->setText("HIIIIIII");

    msgBox->show();
    return a.exec();
}
