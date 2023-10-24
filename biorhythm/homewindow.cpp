#include "homewindow.h"
#include "ui_homewindow.h"
#include <QVector>
#include <QtMath>
#include <QDateTime>
#include <QDate>
#include <QMessageBox>
HomeWindow::HomeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomeWindow)
{
    ui->setupUi(this);

    customPlot = new QCustomPlot();

    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue));


    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::red));


    customPlot->addGraph();
    customPlot->graph(2)->setPen(QPen(Qt::green));


    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("d. MMMM\nyyyy");
    customPlot->xAxis->setTicker(dateTicker);

    customPlot->xAxis->setLabel("Дата");
    customPlot->yAxis->setLabel("%");


    customPlot->xAxis->setRange(QCPAxisTickerDateTime::dateTimeToKey(QDateTime::currentDateTime()), QCPAxisTickerDateTime::dateTimeToKey(QDateTime::currentDateTime().addDays(30)));
    customPlot->yAxis->setRange(-110, 110);

    customPlot->xAxis2->setVisible(true);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLabels(false);

    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->daysLabel->setText(QString::number(ui->daysSlider->sliderPosition()));

    ui->countDateEdit->setText(QDateTime::currentDateTime().toString("dd.MM.yyyy"));

    customPlot->graph(0)->setName("Физический");
    customPlot->graph(1)->setName("Эмоциональный");
    customPlot->graph(2)->setName("Интеллектуальный");


    connect(ui->calculateButton, &QPushButton::clicked, this, &HomeWindow::tryCalculate);

    connect(ui->daysSlider, &QSlider::valueChanged, [this](){
        ui->daysLabel->setText(QString::number(ui->daysSlider->sliderPosition()));
    });
    ui->verticalLayout->addWidget(customPlot);
}

void HomeWindow::drawGraph(int graphIndex, int phase, ClientInfo info) {

    int d = info.birthDate.daysTo(info.currentDate) - 180;

    double curDate;

    QVector<double> x(360), y(360);
    for (int i=0; i<360; i++) {
        curDate = QCPAxisTickerDateTime::dateTimeToKey(info.currentDate.addDays(-180 + i));
        x[i] = curDate;
        y[i] = qSin(2*M_PI*(d+i)/phase) * 100;

    }
    customPlot->graph(graphIndex)->setData(x, y);

}

void HomeWindow::tryCalculate() {

    auto date = QDateTime::fromString(ui->dateLineEdit->text(), "dd.MM.yyyy");
    auto countDate = QDateTime::fromString(ui->countDateEdit->text(), "dd.MM.yyyy");
    qDebug() << date.isValid();

    if (date.isValid() && countDate.isValid()) {
        calculate(ClientInfo(date, countDate, ui->daysSlider->sliderPosition()));
    } else {
        QMessageBox* msgBox = new QMessageBox(this);
        msgBox->setWindowTitle("Биоритмы");
        msgBox->setText("Неверно указана дата!");
        msgBox->setStandardButtons(QMessageBox::Ok);

        connect(msgBox->button(QMessageBox::Ok), &QPushButton::clicked, this, [msgBox]() {
            msgBox->close();
        });
        msgBox->show();
    }
}

void HomeWindow::calculate(ClientInfo info) {
    customPlot->xAxis->setRange(QCPAxisTickerDateTime::dateTimeToKey(info.currentDate), QCPAxisTickerDateTime::dateTimeToKey(info.currentDate.addDays(info.calcDays)));
    customPlot->yAxis->setRange(-110, 110);
    customPlot->legend->setVisible(true);
    drawGraph(0, 23, info);
    drawGraph(1, 28, info);
    drawGraph(2, 33, info);

    customPlot->replot();

}
HomeWindow::~HomeWindow()
{
    delete ui;
}

