#ifndef TABLEFRUITMODEL_H
#define TABLEFRUITMODEL_H
#include <QAbstractTableModel>
#include <mcl.h>

class PrettyTableModel : public QAbstractTableModel {
public:
    QVector<QVector<QString>> items;
    int typeId;
    PrettyTableModel(QObject *parent, QVector<QVector<QString>> _items, int _typeId) : items(_items), typeId(_typeId) {}
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
                return "Date";

            if (typeId == 0) {
                if (section == 2)
                    return "Section";
                if (section == 3)
                    return "Amount";
            }
            if (typeId == 1) {
                if (section == 2)
                  return "Price";
            }
            if (typeId == 2) {
                if (section == 2)
                    return "Section";
                if (section == 3)
                    return "Amount";
                if (section == 4)
                    return "Price";
            }

        }

        return QVariant();
    }

};


#endif // TABLEFRUITMODEL_H
