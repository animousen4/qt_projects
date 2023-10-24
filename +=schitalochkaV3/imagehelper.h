#ifndef IMAGEHELPER_H
#define IMAGEHELPER_H
#include <QString>
class ImageHelper {
public:
    static QString getAvatar(QString path) {
        if (path.isEmpty())
            return ":/images/res-data/default_avatar.png";
        return path;
    }

    static QString getWreath() {
        return ":/images/res-data/wreath.png";
    }
};
#endif // IMAGEHELPER_H
