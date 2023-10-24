#ifndef PRESET_H
#define PRESET_H
#include <QList>
#include "participantinfo.h"
class Preset {
public:
    static QList<ParticipantInfo> getDefaultParticipants() {
        return {
            ParticipantInfo("Лужкова Ульяна", ":/participants-images/res-data/default-participants/uliana.jpg"),
            ParticipantInfo("Медведев Илья", ":/participants-images/res-data/default-participants/ilyaM.jpg"),
            ParticipantInfo("Гнилозуб Кирилл", ":/participants-images/res-data/default-participants/kirill.png"),
            ParticipantInfo("Козыро Илья", ":/participants-images/res-data/default-participants/ilyaK.png"),
            ParticipantInfo("Фролова Илона", ":/participants-images/res-data/default-participants/ilona.jpg"),
            ParticipantInfo("Зайцев Данила", ":/participants-images/res-data/default-participants/danila.jpg"),
            ParticipantInfo("Яцукевич егор", ""),
            ParticipantInfo("Цыбулька Влад", ":/participants-images/res-data/default-participants/vlad.jpg"),
            ParticipantInfo("Фельдшеров Петр", ""),
        };
    }
};
#endif // PRESET_H
