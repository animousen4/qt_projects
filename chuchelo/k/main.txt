#include "gamewindow.h"

#include <QApplication>
#include "gamesettings.h"
#include "menudialog.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setOverrideCursor(QCursor(QPixmap(":/images/res/images/bita.png").scaled(25,25)));
    MenuDialog menu;
    menu.show();
    return a.exec();
}
