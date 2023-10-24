
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "CalculatorKernel.h"
#include <QMap>
#include <QVBoxLayout>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    CalculatorKernel * calculatorKernel;
    QLabel * completionLabel;
    QMap<QChar, double> variables;
    Ui::MainWindow *ui;
    SolvedError recommendedExpression;
    bool isVariableValid;

    QVBoxLayout * variablesLayout;
    void validateForm();
    void expressionChanged(QString text);
    void varValueChanged(QChar variable, double value);
    void revalidate();
    void calculate();
    void onCompletionAccepted();

};

#endif // MAINWINDOW_H
