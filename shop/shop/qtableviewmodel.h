#ifndef QTABLEVIEWMODEL_H
#define QTABLEVIEWMODEL_H

#include <QModelIndex>
#include "fruit.h"
#include <QVector>
#include <QString>

class FruitTableModel : public QAbstractListModel
{
public:
    int id;
    FruitTableModel(QObject *parent, QVector < QVector <QString> >, int);
    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    QVector < QVector<QString> > items;

private:
    //QVector <s1> *values;
};

#endif // QTABLEVIEWMODEL_H
