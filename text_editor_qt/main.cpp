#include "mainwindoweditor.h"
#include <iostream>
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowEditor w;
    w.show();
    return a.exec();
}
