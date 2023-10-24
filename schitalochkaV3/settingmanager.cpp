#include "settingmanager.h"
#include <QDebug>
#include <QDir>
SettingManager::SettingManager(QObject *parent)
    : QObject{parent}
{

    QString filePath = QDir::tempPath() + "/schitalochka";
    qDebug() << filePath;
    QFile file(filePath + "/settings.st");

    qDebug() << "Opening file...";
    file.open(QFile::ReadOnly);
    QDataStream s(&file);
    if (file.isOpen()) {
        gameInfo = new GameInfo;
        s >> *gameInfo;

        qDebug() << "Received data!";
        //qDebug() << gameInfo->participants.length();
    } else {
        if (!QDir(filePath).exists())
            QDir().mkdir(filePath);
        file.open(QFile::WriteOnly);
        gameInfo = new GameInfo({}, -1, {}, -1);
        s << *gameInfo;
        qDebug() << "Writed a new data!";
    }

    file.close();
    emit gameInfoChanged();

}
bool SettingManager::hasParticipant(QString name) {

    for (auto p : gameInfo->participants) {
        if (p.studentName == name)
            return true;
    }

    return false;
}
void SettingManager::changeCountingNumber(int number) {
    gameInfo->countingNumber = number;
    save();
    emit gameInfoChanged();
}
void SettingManager::changeGameInfo(GameInfo _gameInfo) {
    gameInfo = new GameInfo(_gameInfo);
    save();
    emit gameInfoChanged();
}
void SettingManager::changeParticipantList(QList<ParticipantInfo> _pl) {
    gameInfo->participants = _pl;
    save();
    emit gameInfoChanged();
}
void SettingManager::changeParticipantStartNumber(int number) {
    gameInfo->participantStartNumber = number;
    save();
    emit gameInfoChanged();
}
void SettingManager::changeCountingsList(QList<QString> _co) {
    gameInfo->countings = _co;
    save();
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
    QString filePath = QDir::tempPath() + "/schitalochka";
    QFile file(filePath + "/settings.st");

    file.open(QFile::WriteOnly);
    QDataStream s(&file);

    s << *gameInfo;
    file.close();

    qDebug() << "Data saved!";
}
