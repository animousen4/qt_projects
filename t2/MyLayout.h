#ifndef MYLAYOUT_H
#define MYLAYOUT_H

#include <QLayout>
#include <QList>
#include <math.h>

class MyLayout : public QLayout
{
    Q_OBJECT
public:

    QLayoutItem* itemAt(int index) const override {
        if (index >= 0 && index < players.size()) {
            return players.at(index);
        }
        return nullptr;
    }

    QLayoutItem* takeAt(int index) override {
        if (index < 0 || index >= players.size())
                return 0;

        QLayoutItem* item = players.takeAt(index);
        invalidate();
        return item;
    }
    int count() const override {
        return players.size();
     }
    QSize minimumSize() const override {
        QSize dop(radius*2 + 125, radius*2 + 30);
        return dop;
    };

    QSize sizeHint() const override {
        //QSize dop(150, 150);
        //return dop;
        return minimumSize();
    };

    void addItem(QLayoutItem* dop) override {
        players.append(dop);
    };

    void removeItem(QLayoutItem* dop) {
        players.removeOne(dop);
    }

    void setGeometry(const QRect &) override {
        int n = players.size();

        double angle = 2 * M_PI / n;
        double cur_angle = 0;

        for (int i = 0; i < n; i++) {
            QLayoutItem* cur = players[i];
            cur->setGeometry(QRect(
                                 minimumSize().width() / 2 + radius * cos(cur_angle), minimumSize().height() / 2 + radius * sin(cur_angle), cur->sizeHint().width(), cur->sizeHint().height()));
            cur_angle += angle;
        }
    };

    int radius;

    MyLayout(QWidget *parent = nullptr, int r = 0) {
        radius = r;
    };
    ~MyLayout() {};

    QList <QLayoutItem*> players;

private:

};


#endif // MYLAYOUT_H
