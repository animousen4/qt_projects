#include "homewindow.h"
#include "ui_homewindow.h"
#include <QVector>
#include <QtMath>
#include <QDateTime>
#include <QDate>
HomeWindow::HomeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomeWindow)
{
    ui->setupUi(this);

    customPlot = new QCustomPlot();

    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue));
    //customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));

    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::red));
    //customPlot->graph(1)->setBrush(QBrush(QColor(0, 0, 255, 20)));

    customPlot->addGraph();
    customPlot->graph(2)->setPen(QPen(Qt::green));
    //customPlot->graph(2)->setBrush(QBrush(QColor(0, 0, 255, 20)));

    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("d. MMMM\nyyyy");

    customPlot->xAxis->setTicker(dateTicker);

    qDebug() << "cur sec:" << QDateTime::currentDateTime().toSecsSinceEpoch();
    customPlot->xAxis->setRangeLower(QDateTime::currentDateTime().toSecsSinceEpoch());
    customPlot->xAxis->setLabel("Дата");
    customPlot->yAxis->setLabel("%");


    customPlot->xAxis->setRange(QDateTime::currentDateTime().toSecsSinceEpoch(), QDateTime::currentDateTime().toSecsSinceEpoch() + 30*24*3600);
    customPlot->yAxis->setRange(-110, 110);

    customPlot->xAxis2->setVisible(true);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLabels(false);

    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);


//    QCPAxisRect *ar = new QCPAxisRect(customPlot);
//    customPlot->plotLayout()->addElement(0, 1, ar);

//    // setup an extra legend for that axis rect:
//    QCPLegend *arLegend = new QCPLegend;
//    ar->insetLayout()->addElement(arLegend, Qt::AlignTop|Qt::AlignRight);
//    arLegend->setLayer("legend");
//    customPlot->setAutoAddPlottableToLegend(false); // would add to the main legend (in the primary axis rect)

//    customPlot->graph()->addToLegend(arLegend);


    ui->daysLabel->setText(QString::number(ui->daysSlider->sliderPosition()));


    customPlot->graph(0)->setName("Физический");
    customPlot->graph(1)->setName("Эмоциональный");
    customPlot->graph(2)->setName("Интеллектуальный");

    ui->dateEdit->clearMinimumDateTime();
    ui->dateEdit->setMinimumDateTime(QDateTime(QDate(1, 1,1), QTime(0, 0)));


    connect(ui->calculateButton, &QPushButton::clicked, this, &HomeWindow::tryCalculate);

    connect(ui->daysSlider, &QSlider::sliderMoved, [this](int pos){
        ui->daysLabel->setText(QString::number(pos));
    });
    connect(ui->daysSlider, &QSlider::sliderPressed, [this](){
        ui->daysLabel->setText(QString::number(ui->daysSlider->sliderPosition()));
    });

    connect(customPlot, &QCustomPlot::mouseMove, this, &HomeWindow::showPointValue);
    ui->verticalLayout->addWidget(customPlot);
}

void HomeWindow::showPointValue(QMouseEvent* event) {


}
void HomeWindow::drawGraph(int graphIndex, int phase, ClientInfo info) {

    // Draw 1 year
    int d = info.birthDate.daysTo(info.currentDate) - 180;

    int startTime = info.currentDate.toSecsSinceEpoch() - 180*24*3600;

    QVector<double> x(360), y(360);

    qDebug() << "Days: " << d;
    qDebug() << "Start time: " << startTime;

    for (int i=0; i<360; i++) {
        x[i] = startTime + i*24*3600;
        y[i] = qSin(2*M_PI*(d+i)/phase) * 100;
    }
    customPlot->graph(graphIndex)->setData(x, y);

}

void HomeWindow::tryCalculate() {

    auto date = QDateTime::fromString(ui->dateLineEdit->text(), "dd.MM.yyyy");
    qDebug() << date.isValid();

    if (date.isValid()) {
        //calculate(ClientInfo(ui->dateEdit->dateTime(), QDateTime::currentDateTime(), ui->daysSlider->sliderPosition()));
        calculate(ClientInfo(date, QDateTime::currentDateTime(), ui->daysSlider->sliderPosition()));
    }
}

void HomeWindow::calculate(ClientInfo info) {
    customPlot->xAxis->setRange(info.currentDate.toSecsSinceEpoch(), info.currentDate.toSecsSinceEpoch() + info.calcDays*24*3600);
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

