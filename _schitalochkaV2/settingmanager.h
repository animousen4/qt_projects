#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#include <QObject>
#include <QList>
#include <QString>
#include "gameinfo.h"
#include <QFile>
#include <QDataStream>
class SettingManager : public QObject
{
    Q_OBJECT
public:
    explicit SettingManager(QObject *parent = nullptr);
    GameInfo * gameInfo;

    void save();

    void addParticipant(ParticipantInfo _pi);
signals:
    void gameInfoChanged();
};

#endif // SETTINGMANAGER_H
