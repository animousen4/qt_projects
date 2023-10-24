#ifndef MCL_H
#define MCL_H
#include <QDataStream>
#include <QTextStream>
#include <QFile>
#include <QVector>
struct Campus {
    int id;
    QString secondName;

    QString toString() {
        return QString("id: %0; second name: %1").arg(id).arg(secondName);
    }

    bool operator<(const Campus& other) {
        return secondName < other.secondName;
    }
    friend QDataStream& operator<<(QDataStream& out, Campus& s) {
        out << s.id << s.secondName;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, Campus& s) {
        in >> s.id >> s.secondName;
        return in;
    }

    friend QTextStream& operator<<(QTextStream& out, Campus& s) {
        out << s.id << s.secondName;
        return out;
    }

    friend QTextStream& operator>>(QTextStream& in, Campus& s) {
        in >> s.id >> s.secondName;
        return in;
    }
};

struct Library : Campus{
    int price;

    QString toString() {
        return Campus::toString() + QString("; price: %0").arg(price);
    }



    friend QDataStream& operator<<(QDataStream& out, Library& s) {
        out << static_cast<Campus&>(s) << s.price;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, Library& s) {
        in >> static_cast<Campus&>(s) >> s.price;
        return in;
    }

    friend QTextStream& operator<<(QTextStream& out, Library& s) {
        out << static_cast<Campus&>(s) << s.price;
        return out;
    }

    friend QTextStream& operator>>(QTextStream& in, Library& s) {
        in >> static_cast<Campus&>(s) >> s.price;
        return in;
    }
};
template<class T>
class Stud {
    QVector<T> mas;
    int size;

public:

    QVector<T> getAll() {
        return mas;
    }

    void fromText(QFile& file) {
        mas = {};
        file.open(QFile::ReadOnly);
        QTextStream s(&file);
        size = 0;
        while(!s.atEnd()) {
            T obj;
            s >> obj;
            mas.append(obj);
            size++;
        }
        file.close();
    }

    void fromBin(QFile& file) {
        mas = {};
        file.open(QFile::ReadOnly);
        QDataStream s(&file);
        size = 0;
        while(!s.atEnd()) {
            T obj;
            s >> obj;
            mas.append(obj);
            size++;
        }
        file.close();
    }

    void toText(QFile& file) {
        file.open(QFile::WriteOnly);
        QTextStream s(&file);
        for (int i=0; i< size; i++) {
            s << mas[i];
        }
        file.close();
    }

    void toBin(QFile& file) {
        file.open(QFile::WriteOnly);
        QDataStream s(&file);
        for (int i=0; i< size; i++) {
            s << mas[i];
        }
        file.close();
    }


    void sortStud() {
        std::sort(mas.begin(), mas.end(), [](T a, T b){
            return a < b;
        });
    }

    QString toString() {
        QString s;
        for (auto el : mas)
            s += el.toString() + "\n";

        return s;
    }

    T findStud(int id) {

    }
};
#endif // MCL_H
