#ifndef MCL_H
#define MCL_H
#include <QDataStream>
#include <QTextStream>
#include <QFile>
#include <QVector>
#include <QDebug>
#include <QDateTime>
struct BaseData {
    QString name;
    QString date;
};
struct ExtraPrice {
    double price;
};
struct Price : BaseData, ExtraPrice {

    QString toString() {
        return QString("%0 - %1 - %2").arg(name).arg(date).arg(price);
    }

    QVector<QString> getItems(){
        return {name, date, QString::number(price)};
    }

    bool operator<(const Price& other) {
        return name < other.name;
    }

    bool operator>(const Price& other) {
        return name > other.name;
    }

    bool operator==(const Price& other) const {
        return name == other.name;
    }
    friend QDataStream& operator<<(QDataStream& out, Price& s) {
        out << s.name << s.date << s.price;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, Price& s) {
        in >> s.name >> s.date >> s.price;
        return in;
    }

    friend QTextStream& operator<<(QTextStream& out, Price& s) {
        out << s.name << "\t" << s.date << "\t" << s.price;
        return out;
    }

    friend QTextStream& operator>>(QTextStream& in, Price& s) {
        QString str = in.readLine();
        int index = str.lastIndexOf(" ");

        //s.name = str.mid(0, index);
        s.price = str.mid(index + 1, str.length() - 1).toDouble();

        str = str.mid(0, index);
        index = str.lastIndexOf(" ");

        s.date = str.mid(index + 1, str.length() - 1);

        s.name = str.mid(0, index);

        return in;
    }

};

struct ExtraItems {
    QString section;
    int count;
};
struct Items : BaseData, ExtraItems{

    QString toString() {
        return QString("%0 - %1 - %2 - %3").arg(name).arg(date).arg(section).arg(count);
    }

    QVector<QString> getItems(){
        return {name, date, section, QString::number(count)};
    }

    bool operator<(const Items& other) {
        return name < other.name;
    }

    bool operator>(const Items& other) {
        return name > other.name;
    }

    bool operator==(const Items& other) const {
        return name == other.name;
    }
    friend QDataStream& operator<<(QDataStream& out, Items& s) {
        out << s.name << s.date << s.section << s.count;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, Items& s) {
        in >> s.name >> s.date >> s.section >> s.count;
        return in;
    }

    friend QTextStream& operator<<(QTextStream& out, Items& s) {
        out << s.name << "\t" << s.date << "\t" << s.section << "\t" << s.count;
        return out;
    }

    friend QTextStream& operator>>(QTextStream& in, Items& s) {
        QString str = in.readLine();
        int index = str.lastIndexOf(" ");

        s.count = str.mid(index + 1, str.length() - 1).toInt();

        str = str.mid(0, index);
        index = str.lastIndexOf(" ");
        s.section = str.mid(index + 1, str.length() - 1);

        str = str.mid(0, index);
        index = str.lastIndexOf(" ");
        s.date = str.mid(index + 1, str.length() - 1);

        s.name = str.mid(0, index);

        return in;
    }


};
struct Med : BaseData, ExtraItems, ExtraPrice {

    QVector<QString> getItems(){
        return {name, date, section, QString::number(count), QString::number(price)};
    }

    bool operator<(const Med& other) {
        return name < other.name;
    }

    bool operator>(const Med& other) {
        return name > other.name;
    }

    bool operator==(const Med& other) const {
        return name == other.name;
    }

    QString toString() {
        return QString("%0 - %1 - %2 - %3 -%4").arg(name).arg(date).arg(section).arg(price).arg(count);
    }

    friend QDataStream& operator<<(QDataStream& out, Med& s) {
        out << s.name << s.date << s.section << s.price << s.count;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, Med& s) {
        in >> s.name >> s.date >> s.section >> s.price >> s.count;
        return in;
    }

    friend QTextStream& operator<<(QTextStream& out, Med& s) {
        out << s.name << "\t" << s.date << "\t" << s.section << "\t" << s.price << "\t" << s.count;
        return out;
    }

    friend QTextStream& operator>>(QTextStream& in, Med& s) {
        QString str = in.readLine();

        int indexL = str.lastIndexOf(" ");
        s.count = str.mid(indexL + 1, str.length() - 1).toInt();
        str = str.mid(0, indexL); // without count

        indexL = str.lastIndexOf(" ");
        s.price = str.mid(indexL + 1, str.length()-1).toInt();

        str = str.mid(0, indexL); // whitout price
        indexL = str.lastIndexOf(" ");
        s.section = str.mid(indexL + 1, str.length()-1);

        str = str.mid(0, indexL); // without section
        indexL = str.lastIndexOf(" ");
        s.date = str.mid(indexL + 1, str.length()-1);

        str = str.mid(0, indexL); // without date
        indexL = str.lastIndexOf(" ");
        s.name = str.mid(indexL + 1, str.length()-1);

        return in;
    }
};

template<class T>
class MED {
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

    T* selectWithLatestDate(QString name) {
        QVector<T> other;

        std::copy_if(mas->begin(), mas->end(), std::back_inserter(other), [name](T& a){
            return a.name == name;
        });

        std::sort(other.begin(), other.end(), [](T& a, T&b){
            return QDateTime::fromString(a.date, "mm.yyyy") >  QDateTime::fromString(b.date, "mm.yyyy");
        });

        return other.isEmpty() ? nullptr : new T(other.first());

    }

    QVector<T> findBadMedicine(QString date) {
        QVector<T> res;
        std::copy_if(mas->begin(), mas->end(), std::back_inserter(res), [date](T& a){
            return QDateTime::fromString(a.date, "mm.yyyy") < QDateTime::fromString(date, "mm.yyyy");
        });
        return res;
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
            return a > b;
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
    MED(const MED& other)
        : mas(new QVector<T>)
    {
        qDebug() << "Call copy constructor";
        std::copy(other.mas->begin(), other.mas->end(), mas->begin());
    }

    // Move constructor.
    MED(MED&& other)
        : mas(other.mas)
    {

        // Release the data pointer from the source object so that
        // the destructor does not free the memory multiple times.
        qDebug() << "Call move constructor";
        other.mas = nullptr;
    }

    MED<T>& operator=(const MED<T>& other)
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
    MED<T>& operator=(MED<T>&& other)
    {
        qDebug() << "operator= &&";
        if (this != &other)
        {
            mas = other.mas;
            other.mas = nullptr;
        }
        return *this;
    }

    static MED<Med> merge(MED<Items>* a, MED<Price>* b) {
        MED<Med> m;

        for (Items elItems : *a->mas) {
            Med med{BaseData{elItems.name,elItems.date}, ExtraItems{elItems.section, elItems.count}, ExtraPrice{0}};

            Price * p = b->selectWithLatestDate(elItems.name);

            if (p != nullptr) {
                med.price = p->price;
                if (QDateTime::fromString(med.date, "mm.yyyy") <  QDateTime::fromString(p->date, "mm.yyyy")) {
                    med.date = p->date;
                }

            }
            m.mas->append(med);
        }

        for (Price elPrice: *b->mas) {
            auto med = std::find_if(m.mas->begin(), m.mas->end(), [elPrice](Med& med){
                    return med.name == elPrice.name;
            });
            if (med == m.mas->end()) {
                Med newMed{BaseData{elPrice.name,elPrice.date}, ExtraItems{"Not defined", 0}, ExtraPrice{elPrice.price}};
                m.mas->append(newMed);
            }
            //Med med{BaseData{elItems.name,elItems.date}, ExtraItems{elItems.section, elItems.count}, ExtraPrice{0}};
        }

        return m;

    }


    MED() {
        mas = new QVector<T>;
    }

};



#endif // MCL_H
