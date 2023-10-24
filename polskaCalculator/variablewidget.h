#ifndef VARIABLEWIDGET_H
#define VARIABLEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
class VariableWidget : public QWidget
{
    Q_OBJECT
public:
    VariableWidget(QWidget *parent, QChar _varName, double _varValue);
    bool validate();
    bool isValid();

    QChar varName;
    double varValue;

private:


    QLineEdit * edit;
signals:
    void valueChanged(QChar variable, double value);
};

#endif // VARIABLEWIDGET_H
