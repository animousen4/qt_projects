#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>
#include <QPushButton>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    return a.exec();
}
