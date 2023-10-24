#ifndef FRUIT_H
#define FRUIT_H

#include "abstractclass.h"
#include <QDebug>
#include <QPair>

class Fruit : public abstractClass
{
public:
    Fruit();

    bool putData(QString) override;
    bool getData(QString) override;
    void merge(abstractClass*, abstractClass*) override;
    void sortItems() override;

    int cntProducts();
    QVector<s1> getFruits();

    s2 findObject(QString) override;
    QVector < QVector <QString> > getItems() override;

private:
    QVector <s1> fruits;
};

#endif // FRUIT_H
