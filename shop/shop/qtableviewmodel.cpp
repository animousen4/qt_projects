#include <QAbstractTableModel>
#include "qtableviewmodel.h"

FruitTableModel::FruitTableModel(QObject *parent, QVector < QVector<QString> > _items, int _id) : items(_items), id(_id) {}

int FruitTableModel::rowCount(const QModelIndex &parent = QModelIndex()) const {
    return items.size();
}

int FruitTableModel::columnCount(const QModelIndex &parent = QModelIndex()) const {
    return 2;
}

QVariant FruitTableModel::data(const QModelIndex &index, int role = Qt::DisplayRole) const {
    if (role == Qt::DisplayRole) {
        auto f = items[index.row()];
        return f[index.column()];
    }

    return QVariant();
}

QVariant FruitTableModel::headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0) {
            return "Name";
        }
        // Потому что все равно у нас максимум 2 столбца,
        // на секцию(№столбца) проверять без смысла
        if (id == 0)
            return "Section";
        if (id == 1)
            return "Amount";
    }

    return QVariant();
}

/*class BagTableModel : public QAbstractTableModel
{
public:
    Bag* items;
    BagTableModel(QObject* parent, Bag* _items) : items(_items) {}
    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return items->size();
    }
    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return 3;
    }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {

        if (role == Qt::DisplayRole) {
            auto f = items->mas[index.row()];
            if (index.column() == 0) {
                return f.name;
            }
            if (index.column() == 1) {
                return f.section;
            }

            return f.num;
        }

        return QVariant();

    }
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            if (section == 0) {
                return "Name";
            }

            if (section == 1)
                return "Section";

            return "Amount";
        }

        return QVariant();
    }
};*/

