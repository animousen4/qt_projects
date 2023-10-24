#ifndef FINDINFO_H
#define FINDINFO_H

#include <QDialog>
#include <QDataStream>
#include <QTextStream>

struct s1 {
    QString name = "";
    QString section = "";

    friend QTextStream& operator >> (QTextStream& in, s1& x) {

        QString line = in.readLine();

        x.section = line.mid(line.lastIndexOf(' ') + 1, line.size());
        line.remove(line.lastIndexOf(' '), line.size() - line.lastIndexOf(' ') + 1);

        while (line[line.size() - 1] == ' ')
            line.remove(line.size() - 1, 1);

        x.name = line;

        return in;
    }

    friend QTextStream& operator << (QTextStream& out, s1& x) {
        out << x.name << '\t' << x.section;
        return out;
    }

    bool operator < (const s1& x) const {
        return name < x.name;
    }

    bool operator == (const s1& x) const {
        return name == x.name;
    }
};

struct s2 : s1 {

    int cnt = 0;

    friend QTextStream& operator >> (QTextStream& in, s2& x) {

        QString line = in.readLine();

        x.cnt = line.mid(line.lastIndexOf(' ') + 1, line.size()).toInt();
        while (line[line.size() - 1] == ' ')
            line.remove(line.size() - 1, 1);

        x.section = line.mid(line.lastIndexOf(' ') + 1, line.size());
        line.remove(line.lastIndexOf(' '), line.size() - line.lastIndexOf(' ') + 1);

        while (line[line.size() - 1] == ' ')
            line.remove(line.size() - 1, 1);

        x.name = line;

        return in;
    }

    friend QTextStream& operator << (QTextStream& out, s2& x) {
        out << x.name << '\t' << x.section;
        return out;
    }
};

namespace Ui {
class FindInfo;
}

class FindInfo : public QDialog
{
    Q_OBJECT

public:
    explicit FindInfo(QWidget *parent = nullptr);
    ~FindInfo();

    void showInfo(s2, s2);

private:
    Ui::FindInfo *ui;
};

#endif // FINDINFO_H
