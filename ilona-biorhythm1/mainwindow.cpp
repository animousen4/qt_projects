#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QPushButton>
#include <QDateEdit>
#include <QLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <qcustomplot.h>
#include <QPen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    date_of_birth = new QDateTime();
    date_to_calculate = new QDateTime();

    //this->setFixedSize(QSize(1200, 800));
    centralWidget()->setStyleSheet("background-color: white");
    this->setWindowTitle("biorhythms");

    QLabel* enterDate = new QLabel();
    enterDate->setText("enter your birth date");
    QFont labelFont = enterDate->font(); labelFont.setPixelSize(18); labelFont.setBold(true);
    enterDate->setFont(labelFont);
    enterDate->resize(enterDate->sizeHint());
    enterDate->setAlignment(Qt::AlignHCenter);
    enterDate->setMaximumHeight(20);
    //enterDate->setStyleSheet("background-color: red");

    date_of_birth_edit = new QLineEdit();
    date_of_birth_edit->setMinimumHeight(40);
    date_of_birth_edit->setMinimumWidth(150);
    QFont dateFont = date_of_birth_edit->font(); dateFont.setPixelSize(18); //dateFont.setWeight(30);
    date_of_birth_edit->setFont(dateFont);
    date_of_birth_edit->setAlignment(Qt::AlignHCenter);
    //date_of_birth_edit->setStyleSheet("background-color: #7FFF00");

    QLabel* enterCalculationDate = new QLabel();
    enterCalculationDate->setText("enter the date you want to calculate");
    //QFont labelFont = enterDate->font(); labelFont.setPixelSize(18); labelFont.setBold(true);
    enterCalculationDate->setFont(labelFont);
    enterCalculationDate->resize(enterCalculationDate->sizeHint());
    enterCalculationDate->setAlignment(Qt::AlignHCenter);
    enterCalculationDate->setMaximumHeight(20);
    //enterDate->setStyleSheet("background-color: red");

    calculation_date_edit = new QLineEdit();
    calculation_date_edit->setMinimumHeight(40);
    calculation_date_edit->setMaximumWidth(180);
    //QFont dateFont = date_of_birth_edit->font(); dateFont.setPixelSize(18); dateFont.setWeight(30);
    calculation_date_edit->setFont(dateFont);
    calculation_date_edit->setAlignment(Qt::AlignHCenter);
    //date_of_birth_edit->setStyleSheet("background-color: #7FFF00");

    QPushButton* assessBtn = new QPushButton("assess");
    QFont buttonFont; buttonFont.setPixelSize(15);// buttonFont.setWeight(25);
    assessBtn->setFont(buttonFont);
    assessBtn->setStyleSheet("background-color: #8E87D1");
    assessBtn->setFixedSize(QSize(150, 40));

    QLayout* enterBlock = new QVBoxLayout();
    enterBlock->addWidget(enterDate);
    enterBlock->addWidget(date_of_birth_edit);
    enterBlock->addWidget(enterCalculationDate);
    enterBlock->addWidget(calculation_date_edit);
    enterBlock->addWidget(assessBtn);
    enterBlock->setAlignment(date_of_birth_edit, Qt::AlignHCenter);
    enterBlock->setAlignment(calculation_date_edit, Qt::AlignHCenter);
    enterBlock->setAlignment(assessBtn, Qt::AlignHCenter);

    QWidget* dateEditWidget = new QWidget;
    //dateEditWidget->setStyleSheet("background-color: yellow");
    dateEditWidget->setMinimumWidth(size().width());
    dateEditWidget->setMaximumHeight(enterDate->size().height() + date_of_birth_edit->size().height() + assessBtn->size().height());
    qDebug() << enterDate->size().height() + date_of_birth_edit->size().height() + assessBtn->size().height();
    dateEditWidget->setLayout(enterBlock);

    QWidget* graphicsViewWidget = new QWidget();
    //graphicsViewWidget->setStyleSheet("background-color: green");
    graphicsViewWidget->setMinimumSize(QSize(size().width(), size().height() - enterDate->size().height() - date_of_birth_edit->size().height() - assessBtn->size().height() + 300 ));

    QVBoxLayout* graphicsBlock = new QVBoxLayout();
    //graphicsBlock->setMargin(10);

    graphics_viewer = new QCustomPlot();
    graphicsBlock->addWidget(graphics_viewer);

    graphicsViewWidget->setLayout(graphicsBlock);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(dateEditWidget);
    mainLayout->addWidget(graphicsViewWidget);
    centralWidget()->setLayout(mainLayout);

    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("dd.MM.yyyy");
    graphics_viewer->xAxis->setTicker(dateTicker);

    graphics_viewer->xAxis->setRange(QCPAxisTickerDateTime::dateTimeToKey(QDateTime::currentDateTime()), QCPAxisTickerDateTime::dateTimeToKey(QDateTime::currentDateTime().addDays(30)));
    graphics_viewer->yAxis->setRange(-110, 110);

    graphics_viewer->addGraph();
    graphics_viewer->graph(0)->setPen(QPen(QColor(Qt::red)));
    graphics_viewer->graph(0)->setName("Physical");

    graphics_viewer->addGraph();
    graphics_viewer->graph(1)->setPen(QPen(QColor(Qt::blue)));
    graphics_viewer->graph(1)->setName("Emotional");

    graphics_viewer->addGraph();
    graphics_viewer->graph(2)->setPen(QPen(QColor(Qt::green)));
    graphics_viewer->graph(2)->setName("Intellectual");

    graphics_viewer->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    graphics_viewer->legend->setVisible(true);

    connect(assessBtn, &QPushButton::clicked, this, &MainWindow::getDate);
}

void MainWindow::paintGraphic(int n_gr, int period) {
    int lived_days = date_of_birth->daysTo(*date_to_calculate) - 365;

    double curDate;

    QVector<double> x(730), y(730);

    for (int i = 0; i < 730; i++) {
        curDate = QCPAxisTickerDateTime::dateTimeToKey(date_to_calculate->addDays(-365 + i));
        x[i] = curDate;
        y[i] = qSin(2 * M_PI * (lived_days + i) / period) * 100;
    }
    graphics_viewer->graph(n_gr)->setData(x, y);
    //
};

void MainWindow::getDate() {
    *date_of_birth = QDateTime::fromString(date_of_birth_edit->text(), "dd.MM.yyyy");
    *date_to_calculate = QDateTime::fromString(calculation_date_edit->text(), "dd.MM.yyyy");

    graphics_viewer->xAxis->setRange(QCPAxisTickerDateTime::dateTimeToKey(*date_to_calculate), QCPAxisTickerDateTime::dateTimeToKey(date_to_calculate->addDays(30)));

    if (!(date_of_birth->isValid() && date_to_calculate->isValid())) {

        if(!date_of_birth->isValid()) qDebug() << "first";
        if(!date_to_calculate->isValid()) qDebug() << "second";

        QMessageBox::critical(NULL,QObject::tr("Attention"),tr("You entered a wrong date"));
    }
    else {
        paintGraphic(0, 23);
        paintGraphic(1, 28);
        paintGraphic(2, 33);
    }
    graphics_viewer->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

