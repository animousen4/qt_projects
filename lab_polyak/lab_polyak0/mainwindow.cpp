#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(size());

    Calculator dop();
    calc = dop;

    connect(ui->enterExp_edit, &QLineEdit::returnPressed, this, &MainWindow::expressionEntered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::expressionEntered() {

    calc.enteredExpression = ui->enterExp_edit->text();
    qDebug() << calc.enteredExpression;

    QString vars = ui->enterVar_edit->text();

    if (vars == "") {
        QMessageBox::warning(this, "Attention","You didn't enter the variables");
        return;
    }
    else calc.assess(vars);

    return;
}
