#include "fruit.h"
#include <QFile>
#include <QMessageBox>
#include <algorithm>

using namespace std;

Fruit::Fruit()
{
}

void Fruit::sortItems() {
   sort(fruits.begin(), fruits.end(), [](s1& a, s1& b){ return a < b; });
};

void Fruit::merge(abstractClass* dop1, abstractClass* dop2) {

    qDebug() << "merge";

    fruits = {};
    for (auto el : static_cast<Fruit*>(dop1)->fruits) {
        fruits.append(el);
    }

    for (auto el : static_cast<Fruit*>(dop2)->fruits) {
        if (!fruits.contains(el)) {
            fruits.append(el);
        }
    }

    for (int i = 0; i < fruits.size(); i++)
        qDebug () << fruits[i].name << " " << fruits[i].section;

    sort(fruits.begin(), fruits.end(), []( s1& a, s1& b ){ return a < b; });

};

bool Fruit::putData(QString fileName) {

    QFile curFile(fileName);
    QTextStream curStream(&curFile);
    curFile.open(QFile::WriteOnly);

    if (!curFile.isOpen()) {
        return false;
    }

    for (int i = 0; i < fruits.size(); i++) {
        curStream << fruits[i] << '\n';
    }

    curFile.close();
    return true;
}

bool Fruit::getData(QString fileName) {

    fruits = {};
    QFile curFile(fileName);
    QTextStream curStream(&curFile);
    curFile.open(QFile::ReadOnly);

    if (!curFile.isOpen()) {
        return false;
    }

    while (!curStream.atEnd())
    {
      s1 dop;
      curStream >> dop;
      fruits.append(dop);
    }

    for (int i = 0; i < fruits.size(); i++) {
        qDebug() << fruits[i].name << " " << fruits[i].section;
    }

    curFile.close();

    return true;
}

int Fruit::cntProducts() {
    return fruits.size();
}

QVector<s1> Fruit::getFruits() {
    return fruits;
};

s2 Fruit::findObject(QString s) {

    s2 dop;
    dop.name = s;

    auto it = find_if(fruits.begin(), fruits.end(), [s](s1& a){ return a.name == s; });
    if (it == fruits.end()) {
        dop.cnt = -1;
    }
    else {
        dop.section = it->section;
        dop.cnt = -2;
    }

    return dop;
}

QVector < QVector <QString> > Fruit::getItems() {

    QVector < QVector <QString> > res;

    for (auto i : getFruits()) {
        res += {i.name, i.section};
    }

    return res;
};
