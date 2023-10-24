#include "mainwindow.h"

#include <QApplication>
#include "gameinfo.h"
#include "participantinfo.h"
#include "menudialog.h"
#include "CountingManager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MenuDialog md;
    md.show();
    return a.exec();
}
