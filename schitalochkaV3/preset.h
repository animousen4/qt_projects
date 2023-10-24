#ifndef PRESET_H
#define PRESET_H
#include <QList>
#include "participantinfo.h"
#include "gameinfo.h"

struct Preset {
public:
    QString name;
    GameInfo data;
};
class StdPresets {
public:
    static QList<Preset> getAllPresets() {
        return {
            {"1 курс 5 группа", getStandartPm5()},
            {"中国派对", getCh()},
            {"Очистить", getEmpty()},
        };
    }

private:
    static GameInfo getStandartPm5() {
        return GameInfo({
                            ParticipantInfo("Лужкова Ульяна", ":/participants-images/res-data/default-participants/uliana.jpg"),
                            ParticipantInfo("Медведев Илья", ":/participants-images/res-data/default-participants/ilyaM.jpg"),
                            ParticipantInfo("Гнилозуб Кирилл", ":/participants-images/res-data/default-participants/kirill.png"),
                            ParticipantInfo("Козыро Илья", ":/participants-images/res-data/default-participants/ilyaK.png"),
                            ParticipantInfo("Фролова Илона", ":/participants-images/res-data/default-participants/ilona.jpg"),
                            ParticipantInfo("Зайцев Данила", ":/participants-images/res-data/default-participants/danila.jpg"),
                            ParticipantInfo("Яцукевич егор", ":/participants-images/res-data/default-participants/egorY.jpg"),
                            ParticipantInfo("Цыбулька Влад", ":/participants-images/res-data/default-participants/vlad.jpg"),
                            ParticipantInfo("Фельдшеров Петр", ":/participants-images/res-data/default-participants/peatya.jpg"),
                        }, -1, {
                            "Раз два три четыре пять, выходи-ка погулять!",
                            "Вышла мышка как-то раз посмотреть, который час. Раз, два, три, четыре, мышка дернула за гири. Вдруг раздался сильный звон. Выходи из круга вон.",
                            "Ехала белка на тележке, продавала всем орешки. Раз, два, три, выходи из круга ты!"
                        }, -1);
    }

    static GameInfo getCh() {
        return GameInfo({
                            ParticipantInfo("程锦乡", ":/participants-images-ch/res-data/ch-participants/c1.jpg"),
                            ParticipantInfo("张一平", ":/participants-images-ch/res-data/ch-participants/c2.png"),
                            ParticipantInfo("郝琳", ":/participants-images-ch/res-data/ch-participants/c3.png"),
                            ParticipantInfo("郭轩昂", ":/participants-images-ch/res-data/ch-participants/c4.jpg"),
                            ParticipantInfo("谢谢您", ":/participants-images-ch/res-data/ch-participants/c5.png"),
                            ParticipantInfo("早晨好", ":/participants-images-ch/res-data/ch-participants/c6.jpg"),
                        }, -1, {
                            "猴子捞月，月亮在水里，水洗不干，大家一起跳",
                            "左手一个拳头，右手一个拳头，两只拳头打一架，左右开弓赢了它",
                            "一 二 三 四 五 六 七 八 九 十",
                            "十个指头互相爱，手指说话真好玩，食指像蜻蜓点水，中指最高显身手，无名指最温柔，小指小而灵活"
                        }, -1);
    }

    static GameInfo getEmpty() {
        return GameInfo({}, -1, {}, -1);
    }
};


#endif // PRESET_H
