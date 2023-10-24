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

class ABS_Med {
public:
    virtual void fromText(QFile& file) = 0;
    virtual void toText(QFile& file) = 0;
    virtual void fromBin(QFile& file) = 0;
    virtual void toBin(QFile& file) = 0;
    virtual void Sort() = 0;
    virtual QString findGoodMedicine(QString date) = 0;
    virtual QVector<QVector<QString>> getItems() = 0;
};

class Medicine_Section: public ABS_Med {
public:
    QVector<Items> * mas;
    int size() {
        return mas->size();
    }

    QString findData(QString name) {
        auto res = std::find_if(mas->begin(), mas->end(), [name](Items& a) {
            return a.name == name;
        });

        return res == nullptr ? "Not found" :res->toString();
    }

    Items* selectWithLatestDate(QString name) {
        QVector<Items> other;

        std::copy_if(mas->begin(), mas->end(), std::back_inserter(other), [name](Items& a){
            return a.name == name;
        });

        std::sort(other.begin(), other.end(), [](Items& a, Items&b){
            return QDateTime::fromString(a.date, "mm.yyyy") >  QDateTime::fromString(b.date, "mm.yyyy");
        });

        return other.isEmpty() ? nullptr : new Items(other.first());

    }

    QString findGoodMedicine(QString date) {
        QVector<Items> res;
        QString output;
        std::copy_if(mas->begin(), mas->end(), std::back_inserter(res), [date](Items& a){
            return QDateTime::fromString(a.date, "mm.yyyy") > QDateTime::fromString(date, "mm.yyyy");
        });
        for (auto item : res) {
            output += item.toString() + "\n";
        }
        return output;
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
            mas = new QVector<Items>;
            file.open(QFile::ReadOnly);
            QTextStream s(&file);
            while(!s.atEnd()) {
                Items obj;
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
            mas = new QVector<Items>;
            file.open(QFile::ReadOnly);
            QDataStream s(&file);
            while(!s.atEnd()) {
                Items obj;
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
        std::sort(mas->begin(), mas->end(), [](Items a, Items b){
            return a > b;
        });
    }


    QString toString() {
        QString s;
        for (auto el : *mas)
            s += el.toString() + "\n";

        return s;
    }


    Medicine_Section() {
        mas = new QVector<Items>;
    }
};

class Medicine_Price: public ABS_Med {
public:
    QVector<Price> * mas;
    int size() {
        return mas->size();
    }

    QString findData(QString name) {
        auto res = std::find_if(mas->begin(), mas->end(), [name](Price& a) {
            return a.name == name;
        });

        return res == nullptr ? "Not found" :res->toString();
    }

    Price* selectWithLatestDate(QString name) {
        QVector<Price> other;

        std::copy_if(mas->begin(), mas->end(), std::back_inserter(other), [name](Price& a){
            return a.name == name;
        });

        std::sort(other.begin(), other.end(), [](Price& a, Price&b){
            return QDateTime::fromString(a.date, "mm.yyyy") >  QDateTime::fromString(b.date, "mm.yyyy");
        });

        return other.isEmpty() ? nullptr : new Price(other.first());

    }

    QString findGoodMedicine(QString date) {
        QVector<Price> res;
        QString output;
        std::copy_if(mas->begin(), mas->end(), std::back_inserter(res), [date](Price& a){
            return QDateTime::fromString(a.date, "mm.yyyy") > QDateTime::fromString(date, "mm.yyyy");
        });
        for (auto item : res) {
            output += item.toString() + "\n";
        }
        return output;
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
            mas = new QVector<Price>;
            file.open(QFile::ReadOnly);
            QTextStream s(&file);
            while(!s.atEnd()) {
                Price obj;
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
            mas = new QVector<Price>;
            file.open(QFile::ReadOnly);
            QDataStream s(&file);
            while(!s.atEnd()) {
                Price obj;
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
        std::sort(mas->begin(), mas->end(), [](Price a, Price b){
            return a > b;
        });
    }

    QString toString() {
        QString s;
        for (auto el : *mas)
            s += el.toString() + "\n";

        return s;
    }


    Medicine_Price() {
        mas = new QVector<Price>;
    }
};

class Medicine_All: public ABS_Med {
public:
    QVector<Med> * mas;
    int size() {
        return mas->size();
    }

    QString findData(QString name) {
        auto res = std::find_if(mas->begin(), mas->end(), [name](Med& a) {
            return a.name == name;
        });

        return res == nullptr ? "Not found" :res->toString();
    }

    Med* selectWithLatestDate(QString name) {
        QVector<Med> other;

        std::copy_if(mas->begin(), mas->end(), std::back_inserter(other), [name](Med& a){
            return a.name == name;
        });

        std::sort(other.begin(), other.end(), [](Med& a, Med&b){
            return QDateTime::fromString(a.date, "mm.yyyy") >  QDateTime::fromString(b.date, "mm.yyyy");
        });

        return other.isEmpty() ? nullptr : new Med(other.first());

    }

    QString findGoodMedicine(QString date) {
        QVector<Med> res;
        QString output;
        std::copy_if(mas->begin(), mas->end(), std::back_inserter(res), [date](Med& a){
            return QDateTime::fromString(a.date, "mm.yyyy") > QDateTime::fromString(date, "mm.yyyy");
        });
        for (auto item : res) {
            output += item.toString() + "\n";
        }
        return output;
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
            mas = new QVector<Med>;
            file.open(QFile::ReadOnly);
            QTextStream s(&file);
            while(!s.atEnd()) {
                Med obj;
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
            mas = new QVector<Med>;
            file.open(QFile::ReadOnly);
            QDataStream s(&file);
            while(!s.atEnd()) {
                Med obj;
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
        std::sort(mas->begin(), mas->end(), [](Med a, Med b){
            return a > b;
        });
    }

    QString toString() {
        QString s;
        for (auto el : *mas)
            s += el.toString() + "\n";

        return s;
    }


    Medicine_All() {
        mas = new QVector<Med>;
    }
};




#endif // MCL_H
