#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H
#include <QString>
#include <QList>
#include <QMap>
#include "physsettings.h"
#include "movementsettings.h"
#include "vec.h"
class GameSettings {
public:
    double hp;
    double hitStrength;
    int triggerRadius;
    Vec2D borderPadding;
    PhysSettings physSettings;
    MovementSettings movementSettings;
    QList<QString> images;


    GameSettings(double _hp, double _hitStrength, int _triggerRadius, PhysSettings _physSettings, MovementSettings _movementSettings, QList<QString> _images) :
        hp(_hp),
        hitStrength(_hitStrength),
        physSettings(_physSettings),
        movementSettings(_movementSettings),
        images(_images),
        triggerRadius(_triggerRadius) {

    }
    GameSettings(double _hp, double _hitStrength, PhysSettings _physSettings, MovementSettings _movementSettings) :
        hp(_hp),
        hitStrength(_hitStrength),
        physSettings(_physSettings),
        movementSettings(_movementSettings),
        images(defaultImages()),
        triggerRadius(150),
        borderPadding(Vec2D{50,50}) {

    }

    static QList<QString> defaultImages() {
        return {
            ":/images/res/images/zu-10.png",
            ":/images/res/images/zu-40.png",
            ":/images/res/images/zu-70.png",
            ":/images/res/images/zu.jpg"
        };
    }

    QString damageSound() {
        return "qrc:/sounds/res/sounds/damage.mp3";
    }

    QString endSong() {
        return "qrc:/sounds/res/sounds/sad-song.mp3";
    }

    QString katafImage() {
        return ":/images/res/images/kataf.png";
    }

    static GameSettings easy() {
        return GameSettings(100, 30, PhysSettings(1.0), MovementSettings(2.0, 0.8));
    }
    static GameSettings medium() {
        return GameSettings(150, 30, PhysSettings(1.2), MovementSettings(3.0, 1.0));
    }
    static GameSettings hard() {
        return GameSettings(300, 30, PhysSettings(1.7), MovementSettings(5.0, 2.0));
    }


    static QMap<QString, GameSettings> gameSettings() {
        return {
            {"Сложный",hard()},
            {"Средний", medium()},
            {"Легкий",easy()},

        };
    }


};
#endif // GAMESETTINGS_H
