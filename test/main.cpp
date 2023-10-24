#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMessageBox::information(nullptr, "Title", "Message on app start up.");
    MainWindow w;
    w.show();
    return a.exec();
}
