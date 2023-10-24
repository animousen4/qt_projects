#ifndef ABSTRACTCLASS_H
#define ABSTRACTCLASS_H

#include <QString>
#include "findinfo.h"

class abstractClass
{
public:
    abstractClass();
    virtual void merge(abstractClass*, abstractClass*) = 0;
    virtual void sortItems() = 0;
    virtual bool getData(QString) = 0;
    virtual bool putData(QString) = 0;
    virtual QVector <QVector <QString> > getItems() = 0;
    virtual s2 findObject(QString) = 0;
};

#endif // ABSTRACTCLASS_H
