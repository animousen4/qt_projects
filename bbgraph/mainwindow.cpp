#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QtMath>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    graphic = new QCustomPlot();
    graphic->addGraph();
    graphic->addGraph();
    graphic->addGraph();
    graphic->graph(0)->setPen(QPen(QColor(0,0,255), 3));
    graphic->graph(1)->setPen(QPen(QColor(0, 255,0), 3));
    graphic->graph(2)->setPen(QPen(QColor(0,255,255), 3));
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("dd.MM.yyyy");
    graphic->xAxis->setTicker(dateTicker);
    graphic->xAxis->setLabel("Дата");
    graphic->yAxis->setLabel("Процент %");
    graphic->yAxis->setRange(-130, 130);
    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
    setFixedSize(size());
    ui->verticalLayout->addWidget(graphic);

}
double MainWindow::calc(int d, int p) {
    return qSin(2*M_PI*(d)/p) * 100;
}
void MainWindow::buildGraphic(QDateTime b, QDateTime r) {
    if (b.isValid() && r.isValid()) {
        graphic->xAxis->setRange(QCPAxisTickerDateTime::dateTimeToKey(r), QCPAxisTickerDateTime::dateTimeToKey(r.addDays(30)));
        QDateTime temp = r;

        QVector<double> y1(30), y2(30), y3(30);
        QVector<double> x1(30), x2(30), x3(30);
        for (int i = 0; i < 30; i++) {
            // 23 28 33
            x1[i] = QCPAxisTickerDateTime::dateTimeToKey(temp);
            y1[i] = calc(b.daysTo(temp), 23);

            x2[i] = QCPAxisTickerDateTime::dateTimeToKey(temp);
            y2[i] = calc(b.daysTo(temp), 28);

            x3[i] = QCPAxisTickerDateTime::dateTimeToKey(temp);
            y3[i] = calc(b.daysTo(temp), 33);


            temp = temp.addDays(1);
        }

        graphic->graph(0)->setData(x1, y1);
        graphic->graph(1)->setData(x2, y2);
        graphic->graph(2)->setData(x3, y3);

        graphic->replot();
    } else {
        qDebug() << "Fail";
        QMessageBox* msgBox = new QMessageBox(this);
        msgBox->setText("введите дату верно");
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->show();
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    buildGraphic(QDateTime::fromString(ui->lineEdit->text(), "dd.MM.yyyy"), QDateTime::fromString(ui->lineEdit_2->text(), "dd.MM.yyyy"));
}

