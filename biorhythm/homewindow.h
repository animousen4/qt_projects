#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QMainWindow>
#include "clientinfo.h"
#include "qcustomplot/qcustomplot.h"
QT_BEGIN_NAMESPACE
namespace Ui { class HomeWindow; }
QT_END_NAMESPACE

class HomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    HomeWindow(QWidget *parent = nullptr);
    ~HomeWindow();

private:
    Ui::HomeWindow *ui;
    QCustomPlot *customPlot;

    void calculate(ClientInfo);
    void tryCalculate();
    void drawGraph(int graphIndex, int phase, ClientInfo info);
};
#endif // HOMEWINDOW_H
