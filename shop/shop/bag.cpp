#include "bag.h"
#include <QDebug>
#include <QFile>
#include <QVector>

using namespace std;

Bag::Bag()
{

}

void Bag::merge(abstractClass* dop1, abstractClass* dop2) {
    products = {};
    for (auto el : static_cast<Bag*>(dop1)->products) {
        products.append(el);
    }

    for (auto el : static_cast<Bag*>(dop2)->products) {
        if (!products.contains(el)) {
            products.append(el);
        }
    }

    for (int i = 0; i < products.size(); i++)
        qDebug () << products[i].name << " " << products[i].section;

    sort(products.begin(), products.end(), []( s2& a, s2& b ){ return a < b; });
};

void Bag::sortItems() {
    sort(products.begin(), products.end(), [](s2& a, s2& b){ return a < b; });
};

bool Bag::getData(QString fileName) {
    products = {};
    QFile curFile(fileName);
    QTextStream curStream(&curFile);
    curFile.open(QFile::ReadOnly);

    if (!curFile.isOpen()) {
        return false;
    }

    while (!curStream.atEnd())
    {
      s2 dop;
      curStream >> dop;
      products.append(dop);
    }

    for (int i = 0; i < products.size(); i++) {
        qDebug() << products[i].name << " " << products[i].section << " " << products[i].cnt;
    }

    curFile.close();

    return true;
};

bool Bag::putData(QString fileName) {
    QFile curFile(fileName);
    QTextStream curStream(&curFile);
    curFile.open(QFile::WriteOnly);

    if (!curFile.isOpen()) {
        return false;
    }

    for (int i = 0; i < products.size(); i++) {
        curStream << products[i] << '\n';
    }

    curFile.close();
    return true;
};

QVector <QVector <QString> > Bag::getItems() {
    QVector < QVector <QString> > res;

    for (auto i : getProducts()) {
        res += {i.name, i.section, QString::number(i.cnt)};
    }

    return res;
};

s2 Bag::findObject(QString s) {
    s2 dop;
    dop.name = s;

    auto it = find_if(products.begin(), products.end(), [s](s1& a){ return a.name == s; });
    if (it == products.end()) {
        dop.cnt = -1;
    }
    else {
        dop.section = it->section;
        dop.cnt = it->cnt;
    }

    return dop;
};
