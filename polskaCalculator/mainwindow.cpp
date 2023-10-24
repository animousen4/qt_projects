
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QMap>
#include <QLabel>
#include "variablewidget.h"
#include <QCompleter>
const QString redColor = "background-color: rgb(255,153,153);";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    completionLabel = new QLabel();
    completionLabel->setStyleSheet("font: bold 12px");

    ui->errorResultLabel->hide();
    ui->completionWidget->hide();
    ui->completionButton->setLayout(new QHBoxLayout());
    ui->completionButton->layout()->addWidget(completionLabel);
    ui->completionButton->layout()->setContentsMargins(QMargins(5,0,0,0));

    isVariableValid = true;
    calculatorKernel = new CalculatorKernel;

    variablesLayout = new QVBoxLayout(ui->scrollArea->widget());
    variablesLayout->setAlignment(Qt::AlignTop);

    connect(ui->expressionEdit, &QLineEdit::textChanged, this, &MainWindow::expressionChanged);
    connect(ui->completionButton, &QPushButton::clicked, this, &MainWindow::onCompletionAccepted);

}
void MainWindow::onCompletionAccepted() {
    ui->expressionEdit->setText(completionLabel->text());
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::validateForm(){


}
void MainWindow::varValueChanged(QChar variable, double value) {
    qDebug() << "Var value changed!";
    isVariableValid = true;
    for (int i = 0; i<variablesLayout->count(); i++) {
        VariableWidget * w = static_cast<VariableWidget*>(variablesLayout->itemAt(i)->widget());
        if (!w->isValid()) {
            isVariableValid = false;
            break;
        }
    }
    variables.insert(variable, value);
    revalidate();
}

void MainWindow::calculate() {
    ui->lcdNumber->display(QString::number(calculatorKernel->calculateAll(ui->expressionEdit->text(), variables)));
}
void MainWindow::revalidate(){
    ui->errorLabel->setText("");
    ui->errorResultLabel->hide();
    ui->lcdNumber->show();
    ui->completionWidget->hide();
    ui->expressionEdit->setStyleSheet("");

    // COMMON
    if (isVariableValid && !recommendedExpression.hasError()) {
        calculate();
    } else {
        ui->lcdNumber->hide();
        ui->errorResultLabel->show();

    }

    // INDIVIDUAL
    if (!isVariableValid) {
        ui->errorLabel->setText("Correct the highlighted fields");
    }

    if (recommendedExpression.hasError()) {
        completionLabel->setText(recommendedExpression.expression);
        ui->completionWidget->show();
        ui->errorLabel->setText(recommendedExpression.errors.first());
        ui->expressionEdit->setStyleSheet(redColor);
    }
}
void MainWindow::expressionChanged(QString text) {
    QList<QChar> reqVars = calculatorKernel->getRequiredVars(text);
    while(QLayoutItem * item = variablesLayout->takeAt(0)) {
        variablesLayout->removeWidget(item->widget());
        item->widget()->deleteLater();
        delete item;
    }
    for (QChar c : reqVars) {
        if (!variables.contains(c)) {
            variables.insert(c, 0);
        }
       auto varWidget = new VariableWidget(nullptr, c, variables[c]);
       connect(varWidget, &VariableWidget::valueChanged, this, &MainWindow::varValueChanged);
       variablesLayout->addWidget(varWidget);
    }

    isVariableValid = true;
    recommendedExpression = calculatorKernel->getCorrectExpression(text);
    revalidate();

}

