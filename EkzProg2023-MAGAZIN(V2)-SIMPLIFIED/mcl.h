#ifndef MCL_H
#define MCL_H
#include <QDataStream>
#include <QTextStream>
#include <QFile>
#include <QVector>
#include <QDebug>

struct S1 {
    QString name;
    QString section;

    QString toString() {
        return QString("%0 - %1").arg(name).arg(section);
    }

    QVector<QString> getItems(){
        return {name, section};
    }

    bool operator<(const S1& other) {
        return name < other.name;
    }

    bool operator>(const S1& other) {
        return name > other.name;
    }

    bool operator==(const S1& other) const {
        return name == other.name;
    }
    friend QDataStream& operator<<(QDataStream& out, S1& s) {
        out << s.name << s.section;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, S1& s) {
        in >> s.name >> s.section;
        return in;
    }

    friend QTextStream& operator<<(QTextStream& out, S1& s) {
        out << s.name << "\t" << s.section;
        return out;
    }

    friend QTextStream& operator>>(QTextStream& in, S1& s) {
        QString str = in.readLine();
        int index = str.lastIndexOf(" ");

        s.name = str.mid(0, index);
        s.section = str.mid(index + 1, str.length() - 1);

        return in;
    }


};

struct S2 : S1{
    int num;

    QVector<QString> getItems(){
        return {name, section, QString::number(num)};
    }
    QString toString() {
        return S1::toString() + QString(" - %0").arg(num);
    }

    friend QDataStream& operator<<(QDataStream& out, S2& s) {
        out << static_cast<S1&>(s) << s.num;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, S2& s) {
        in >> static_cast<S1&>(s) >> s.num;
        return in;
    }

    friend QTextStream& operator<<(QTextStream& out, S2& s) {
        out << static_cast<S1&>(s) << "\t" << s.num;
        return out;
    }

    friend QTextStream& operator>>(QTextStream& in, S2& s) {
        QString str = in.readLine();
        int indexL = str.lastIndexOf(" ");

        s.section = str.mid(indexL + 1, str.length() - 1);
        str = str.mid(0, indexL); // without section

        indexL = str.lastIndexOf(" ");

        s.num = str.mid(indexL + 1, str.length()-1).toInt();

        s.name = str.mid(0, indexL);

        return in;
    }

    S2 operator+(const S2& other) {
        return S2{name, section, num + other.num};
    }
};


class ABS_COMP {

public:
    virtual int size() = 0;
    virtual void fromText(QFile& file) = 0;
    virtual void toText(QFile& file) = 0;
    virtual void fromBin(QFile& file) = 0;
    virtual void toBin(QFile& file) = 0;
    virtual void Sort() = 0;
    virtual QString toString() = 0;
    virtual void merge(ABS_COMP* a, ABS_COMP* b) = 0;
    virtual int getCount() = 0;
    virtual QString findData(QString name) = 0;
    virtual QVector<QVector<QString>> getItems() = 0;

};


template<class T>
class ProxyClass : public ABS_COMP {
public:
    QVector<T> * mas;
    int size() {
        return mas->size();
    }


    QString findData(QString name) {
        auto res = std::find_if(mas->begin(), mas->end(), [name](T& a) {
            return a.name == name;
        });

        return res == nullptr ? "Not found" :res->toString();
    }


    QVector<QVector<QString>> getItems() {
        QVector<QVector<QString>> res;

        for (auto i : *mas) {
            res += i.getItems();
        }

        return res;
    }
    void fromText(QFile& file) {
            delete mas;
            mas = new QVector<T>;
            file.open(QFile::ReadOnly);
            QTextStream s(&file);
            while(!s.atEnd()) {
                T obj;
                s >> obj;
                mas->append(obj);
            }
            file.close();
    }


    void toText(QFile& file) {
        file.open(QFile::WriteOnly);
        QTextStream s(&file);
        for (int i=0; i< mas->count(); i++) {
            s << (*mas)[i] << "\n";
        }
        file.close();
    }


    void fromBin(QFile& file) {
            delete mas;
            mas = new QVector<T>;
            file.open(QFile::ReadOnly);
            QDataStream s(&file);
            while(!s.atEnd()) {
                T obj;
                s >> obj;
                mas->append(obj);
            }
            file.close();
    }
    void toBin(QFile& file) {
            file.open(QFile::WriteOnly);
            QDataStream s(&file);
            for (int i=0; i < mas->size(); i++) {
                s << (*mas)[i];
            }
            file.close();
        }


    void Sort() {
        std::sort(mas->begin(), mas->end(), [](T a, T b){
            return a < b;
        });
    }

    int getCount() {
        return mas->count();
    }


    QString toString() {
        QString s;
        for (auto el : *mas)
            s += el.toString() + "\n";

        return s;
    }

    // Copy constructor.
    ProxyClass(const ProxyClass& other)
        : mas(new QVector<T>)
    {
        qDebug() << "Call copy constructor";
        std::copy(other.mas->begin(), other.mas->end(), mas->begin());
    }

    // Move constructor.
    ProxyClass(ProxyClass&& other)
        : mas(other.mas)
    {

        // Release the data pointer from the source object so that
        // the destructor does not free the memory multiple times.
        qDebug() << "Call move constructor";
        other.mas = nullptr;
    }

    ProxyClass<T>& operator=(const ProxyClass<T>& other)
        {
            qDebug() << "operator= &";
            if (this != &other)
            {
                // Free the existing resource.
                delete mas;
                mas = new QVector<T>;
                std::copy(other.mas->begin(), other.mas->end(), mas->begin());
            }
            return *this;
        }

        // Move assignment operator.
    ProxyClass<T>& operator=(ProxyClass<T>&& other)
    {
        qDebug() << "operator= &&";
        if (this != &other)
        {
            mas = other.mas;
            other.mas = nullptr;
        }
        return *this;
    }


    ProxyClass() {
        mas = new QVector<T>;
    }

};


class Fruit : public ProxyClass<S1> {
public:
    Fruit() : ProxyClass() {

    }
    ~Fruit() {
        delete mas;
    }
    void merge(ABS_COMP* a, ABS_COMP* b) {
        delete mas;
        mas = new QVector<S1>;
        for (auto el : *static_cast<Fruit*>(a)->mas) {
            mas->append(el);
        }

        for (auto el : *static_cast<Fruit*>(b)->mas) {
            if (!mas->contains(el)) {
                mas->append(el);
            }
        }
    }

};

class Bag : public ProxyClass<S2> {
public:
    Bag() : ProxyClass() {

    }
    ~Bag() {
        delete mas;
    }
    void merge(ABS_COMP* a, ABS_COMP* b) {
        delete mas;
        mas = new QVector<S2>;
        for (auto el : *static_cast<Bag*>(a)->mas) {
            mas->append(el);
        }

        for (auto el : *static_cast<Bag*>(b)->mas) {
            if (mas->indexOf(el) >= 0) {
                (*mas)[mas->indexOf(el)] = (*mas)[mas->indexOf(el)] + el;
            } else {
                mas->append(el);
            }
        }
    }


};


#endif // MCL_H
