#include "gameinfo.h"

GameInfo::GameInfo(QList<ParticipantInfo> _participants, int _participantStartNumber, QList<QString> _countings, int _countingNumber) :
    participants(_participants), participantStartNumber(_participantStartNumber), countings(_countings), countingNumber(_countingNumber)
{

}


GameInfo::GameInfo() {

}
