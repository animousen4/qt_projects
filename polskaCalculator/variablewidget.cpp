#include "variablewidget.h"
#include <QHBoxLayout>

#include <QDoubleValidator>
#include <QLocale>

VariableWidget::VariableWidget(QWidget *parent, QChar _varName, double _varValue)
    : QWidget{parent}, varName(_varName), varValue(_varValue)
{
    QHBoxLayout * layout = new QHBoxLayout;
    QLabel * label = new QLabel;

    edit = new QLineEdit;

    label->setText(QString(varName));
    label->setStyleSheet("font: bold 16px; color: rgb(153,0,76)");

    edit->setText(QString::number(varValue));
    edit->setStyleSheet("font: bold 12px");
    auto validator = new QDoubleValidator(this);
    validator->setLocale(QLocale::C);
    edit->setValidator(validator);
    connect(edit, &QLineEdit::textChanged, this, [this](QString text){
        varValue = text.toDouble();
        validate();
        emit valueChanged(varName, varValue);
    });



    layout->addWidget(label);
    layout->addWidget(edit);
    this->setLayout(layout);
}
bool VariableWidget::isValid() {
    return !edit->text().isEmpty();
}
bool VariableWidget::validate(){
    if (isValid()) {
        edit->setStyleSheet("");
        return true;
    }

    edit->setStyleSheet("background-color: rgb(255,153,153)");
    return false;
}
