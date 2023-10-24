
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVector>
#include <QtMath>
#include <QDebug>
#include <QCalendar>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText(QString("Формат: dd.MM.(-)yyyy"));
    ui->lineEdit_2->setPlaceholderText(QString("Формат: dd.MM.(-)yyyy"));
    ui->check->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    ui->check->hide();
    double a = 0;
    double b =  30;
    double h = 1;
    int N = (b - a) / h + 2;
    QVector<double> x(N), y1(N), y2(N), y3(N);

    QString Birth, Count;
    Birth = ui->lineEdit->text();
    Count = ui->lineEdit_2->text();
    dBirth = QDate::fromString(Birth,"dd.MM.yyyy");
    dCount = QDate::fromString(Count,"dd.MM.yyyy");
    QDate temp;

    temp = dBirth;
    if(dBirth.isValid() && dCount.isValid())
    {
        int days = dBirth.daysTo(dCount);
        qDebug() << days;
        for (double X = a; X <= b; X = X + h) {
            x << QCPAxisTickerDateTime::dateTimeToKey(temp.addDays(days));
            y1 << qSin(2*M_PI*(days)/23)*100;
            y2 << qSin(2*M_PI*(days)/28)*100;
            y3 << qSin(2*M_PI*(days)/33)*100;
            days = days + 1;
            temp = dBirth;
        }
        qDebug() << QCPAxisTickerDateTime::dateTimeToKey(temp.addDays(days));

        ui->widget->clearGraphs();

        ui->widget->addGraph();
        ui->widget->graph(0)->setData(x, y1);
        ui->widget->graph(0)->setPen(QColor("blue"));
        ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

        ui->widget->addGraph();
        ui->widget->graph(1)->setData(x, y2);
        ui->widget->graph(1)->setPen(QColor("red"));
        ui->widget->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

        ui->widget->addGraph();
        ui->widget->graph(2)->setData(x, y3);
        ui->widget->graph(2)->setPen(QColor("green"));
        ui->widget->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

        QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
        ui->widget->xAxis->setTicker(dateTicker);
        ui->widget->xAxis->setRange(QCPAxisTickerDateTime::dateTimeToKey(dCount), QCPAxisTickerDateTime::dateTimeToKey(dCount.addDays(30)));
        dateTicker->setDateTimeFormat("dd.MM.yyyy");

        ui->widget->yAxis->setRange(-100, 100);

        ui->widget->replot();
    }
    else {
        ui->check->show();
        return;
    }
}

