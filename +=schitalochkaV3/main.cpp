#include "mainwindow.h"

#include <QApplication>
#include "gameinfo.h"
#include "participantinfo.h"
#include "menudialog.h"
#include "CountingManager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QResource::registerResource("res.qrc");
    MenuDialog md;
    md.show();
    return a.exec();
}
