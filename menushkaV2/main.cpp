#include "mainwindow.h"

#include <QApplication>
#include <QList>
#include <QDebug>

void sortD() {
    QList<QString> output;
    QString input = "ПАПА";

    QMap<QString, int> map;

    for (int i = 0; i < input.length() - 1; i++) {
        QString key = QString(1, input[i]) + QString(1, input[i+1]);
        QString reversedKey = QString(1, input[i+1]) + QString(1, input[i]);
        if (!map.contains(key)){
            if (!map.contains(reversedKey)) {
                map.insert(key, 1);
            } else {
                int value = map.value(reversedKey);
                map.insert(reversedKey, value+1);
            }
        }else {
            int value = map.value(key);
            map.insert(key, value+1);
        }
    }

    qDebug() << map;

}
int main(int argc, char *argv[])
{
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();

    //sortD();
    return 0;
}
