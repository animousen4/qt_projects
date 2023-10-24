#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //w.startGame();

    w.setGeometry(450, 60, 1000, 950);

    return a.exec();
}
