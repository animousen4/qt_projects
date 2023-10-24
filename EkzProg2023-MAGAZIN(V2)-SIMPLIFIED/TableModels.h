#ifndef TABLEFRUITMODEL_H
#define TABLEFRUITMODEL_H
#include <QAbstractTableModel>
#include <mcl.h>

class PrettyTableModel : public QAbstractTableModel {
public:
    QVector<QVector<QString>> items;
    PrettyTableModel(QObject *parent, QVector<QVector<QString>> _items) : items(_items) {}
    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return items.size();
    }
    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return items.isEmpty() ? 0 : items.first().count();
    }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            auto f = items[index.row()];
            return f[index.column()];
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

};


#endif // TABLEFRUITMODEL_H
