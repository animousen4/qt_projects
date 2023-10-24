#ifndef BAG_H
#define BAG_H
#include "abstractclass.h"

class Bag : public abstractClass
{
public:
    Bag();

    QVector <s2> products;

    void merge(abstractClass*, abstractClass*) override;
    void sortItems() override;
    bool getData(QString) override;
    bool putData(QString) override;
    QVector <QVector <QString> > getItems() override;
    s2 findObject(QString) override;
    QVector <s2> getProducts() { return products; };
};

#endif // BAG_H
