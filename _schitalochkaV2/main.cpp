#include "mainwindow.h"

#include <QApplication>
#include "gameinfo.h"
#include "participantinfo.h"
#include "menudialog.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w(nullptr,
//                 GameInfo(
//                     {
//                         ParticipantInfo("A", "f.jpg"),
//                         ParticipantInfo("B", "f.jpg"),
//                         ParticipantInfo("C", "f.jpg"),
//                         ParticipantInfo("D", "f.jpg"),
//                         ParticipantInfo("E", "f.jpg"),
//                     },
//                     new int(0),
//                     {"sds sd", "fgiodfg"},
//                     new int(0)

//                 ));
//    w.show();
//    w.start();
    MenuDialog md;
    md.show();

    return a.exec();
}
