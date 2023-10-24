#include "mainwindow.h"

#include <QApplication>
#include "gameinfo.h"
#include "participantinfo.h"
#include "menudialog.h"
#include "CountingManager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w(nullptr,
//                 GameInfo(
//                     {
//                         ParticipantInfo("A", "f.jpeg"),
//                         ParticipantInfo("B", "f.jpeg"),
//                         ParticipantInfo("C", "f.jpeg"),
//                         ParticipantInfo("D", "f.jpeg"),
//                         ParticipantInfo("E", "f.jpeg"),
//                     },
//                     0,
//                     {"sds sd", "fgiodfg"},
//                     0

//                 ));
//    w.show();
//    w.start();
    MenuDialog md;
    md.show();

    //qDebug() << CountingManager("fsd fdfd f").getWords();
    //qDebug() << QString("123 fdfdf gsdfg,1423!fs").split(QRegularExpression("!"));
    return a.exec();
}
