#ifndef GAMEINFO_H
#define GAMEINFO_H

#include "participantinfo.h"
#include <QList>
#include <QString>
#include <QDataStream>

class GameInfo
{

public:
    GameInfo(QList<ParticipantInfo> _participants, int _participantStartNumber, QList<QString> _countings, int _countingNumber);
    GameInfo();
    QList<ParticipantInfo> participants;
    int participantStartNumber;

    QList<QString> countings;
    int countingNumber;

    friend QDataStream &operator >>(QDataStream &in, GameInfo &info) {

        in >> info.participants >> info.participantStartNumber >> info.countings >> info.countingNumber;
        return in;
    }

    friend QDataStream &operator <<(QDataStream &out, const GameInfo &info) {
        out << info.participants << info.participantStartNumber << info.countings << info.countingNumber;
        return out;
    }

};

#endif // GAMEINFO_H
