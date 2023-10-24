#ifndef CIRCULARLAYOUT_H
#define CIRCULARLAYOUT_H

#include <QLayout>
#include <QtWidgets>
#include <cmath>
using namespace std;
class CircularLayout : public QLayout {
public:
    CircularLayout(QWidget* parent = nullptr, int radius = 10) : QLayout(parent), m_radius(radius) {

    }
    ~CircularLayout() {}

    // Add widget to layout
    void addItem(QLayoutItem* item) override {
        m_items.append(item);
    }

    // Remove widget from layout
    void removeItem(QLayoutItem* item) {
        m_items.removeOne(item);
    }

    // Return the preferred size of the layout
    QSize sizeHint() const override {
        return minimumSize();
    }

    // Return the minimum size of the layout
    QSize minimumSize() const override {
//        QSize size;
//        int count = m_items.count();
//        for (int i = 0; i < count; ++i) {
//            QLayoutItem* item = m_items.at(i);
//            size = size.expandedTo(item->minimumSize());
//        }
//        int diameter = m_radius * 2;
//        int spacing;
//        if (count != 0) {
//             spacing = diameter / count;
//        } else {
//            spacing = 0;
//        }
        int diameter = m_radius * 2;
        return QSize(diameter, diameter);
    }

    // Set the geometry of each widget in the layout
    void setGeometry(const QRect& rect) override {
        int count = m_items.count();
        bool useMid = false;
        if (count == 0) {
            return;
        }
        if (count == 1) {
            useMid = true;
        }
        double fi = 2 * M_PI / count;
        double curFi = 0;
        for (int i = 0; i < count; ++i) {
            QLayoutItem* item = m_items.at(i);
            int itemWidth = item->sizeHint().width();
            int itemHeight = item->sizeHint().height();
            int itemX = minimumSize().width() / 2 + (useMid ? 0 : m_radius * cos(curFi));
            int itemY = minimumSize().height() / 2 + (useMid ? 0 : m_radius * sin(curFi));
            item->setGeometry(QRect(itemX, itemY, itemWidth, itemHeight));

            curFi = curFi + fi;
            //x += spacing;
        }
    }

    // Return the layout item at the given index
    QLayoutItem* itemAt(int index) const override {
        if (index >= 0 && index < m_items.size()) {
            return m_items.at(index);
        }
        return nullptr;
    }

    QLayoutItem* takeAt(int index) override {
        if (index < 0 || index >= m_items.size())
                return 0;

            QLayoutItem* item = m_items.takeAt(index);
            invalidate();
            return item;
    }

    // Return the number of items in the layout
    int count() const override {
        return m_items.size();
    }


    QList<QLayoutItem*> m_items;
private:
    int m_radius;
};


#endif // CIRCULARLAYOUT_H
