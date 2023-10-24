#ifndef MYCLASS_H
#define MYCLASS_H
#include <iostream>
#include <QString>
#include <QDebug>
#include <QDataStream>
using namespace std;
class MyClass {
    public:
        int num;
        QString str;
        friend QDataStream& operator<<(MyClass& myClass, QDataStream& s) {
            s << myClass.str << myClass.num;
            return s;
        }
};
#endif // MYCLASS_H
