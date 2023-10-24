#ifndef TARGETPROPS_H
#define TARGETPROPS_H
#include <QString>
#include <QObject>
#include <QList>
#include "vec.h"
class TargetProps{
public:
    double hp;
    double maxHp;
    Vec2D picSize;
    QList<QString> imageNames;

    double getHpPercentage(){
        return hp/maxHp;
    }

    QString getImage() {
        double hpP = getHpPercentage();
        double level = (double)1/imageNames.length();
        int index = 0;
        while (hpP>level) {
            hpP = hpP - level;
            index++;
        }

        return imageNames[index];
    }

    TargetProps(double _maxHp, QList<QString> _imagesNames) : hp(_maxHp), maxHp(_maxHp), imageNames(_imagesNames) {
        //picSize = Vec2D{48,60};
        //picSize = Vec2D{72, 90};
        picSize = Vec2D{62, 78};
    }

    bool isAlive () {
        return hp>0;
    }

    void hit(double p) {
        hp = hp - p;
        if (hp<0)
            hp = 0;
    }



};
#endif // TARGETPROPS_H
