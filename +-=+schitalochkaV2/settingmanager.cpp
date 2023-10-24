#include "settingmanager.h"
#include <QDebug>
SettingManager::SettingManager(QObject *parent)
    : QObject{parent}
{
    QFile file("settings.st");

    qDebug() << "Opening file...";
    file.open(QFile::ReadOnly);
    QDataStream s(&file);
    if (file.isOpen()) {
        gameInfo = new GameInfo;
        s >> *gameInfo;

        qDebug() << "Received data!";
        //qDebug() << gameInfo->participants.length();
    } else {
        file.open(QFile::WriteOnly);
        gameInfo = new GameInfo({}, 0, {}, 0);
        s << *gameInfo;
        qDebug() << "Writed a new data!";
    }

    file.close();
    emit gameInfoChanged();
}
void SettingManager::removeParticipant(int index) {
    gameInfo->participants.removeAt(index);
    save();
    emit gameInfoChanged();
}
void SettingManager::addParticipant(ParticipantInfo _pi) {
    gameInfo->participants.push_back(_pi);
    save();
    emit gameInfoChanged();
}

void SettingManager::addCounting(QString counting) {
    gameInfo->countings.push_back(counting);
    save();
    emit gameInfoChanged();
}
void SettingManager::removeCounting(int index) {

    gameInfo->countings.removeAt(index);
    save();
    emit gameInfoChanged();
}
bool SettingManager::isExistCounting(QString counting) {
    return gameInfo->countings.contains(counting);
}




void SettingManager::save() {
    QFile file("settings.st");
    file.open(QFile::WriteOnly);
    QDataStream s(&file);

    s << *gameInfo;
    file.close();

    qDebug() << "Data saved!";
}
