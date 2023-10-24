#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent, GameInfo _gameInfo)
    : QMainWindow(parent), gameInfo(_gameInfo)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (gameInfo.participantStartNumber != -1) {
        currentSelection = gameInfo.participantStartNumber;
    }
    round = 0;
    timesCounted = 1;
    cl = new CircularLayout(nullptr, 250);
    int i = 0;
    for (auto p : gameInfo.participants) {
        auto pw = new ParticipantWidget(p, i);
        connect(this, &MainWindow::unselectAll, pw, &ParticipantWidget::unselect);
        cl->addWidget(pw);
        i = i + 1;
    }


    gameTimer = new QTimer;
    gameTimer->setInterval(1000);
    //gameTimer->setSingleShot(true);
    connect(gameTimer, &QTimer::timeout, this, &MainWindow::timerEmitted);
    ui->centralwidget->setLayout(cl);

    //c->kill();
}
void MainWindow::start() {
//    dynamic_cast<ParticipantWidget*>(cl->itemAt(currentSelection)->widget())->select(currentSelection);
//    timesCounted = timesCounted + 1;
    gameTimer->start();
}

void MainWindow::timerEmitted() {
    if (cl->m_items.length() == 1) {
        gameTimer->stop();
        // game finished
        return;
    }
    qDebug () << QString("Timer emitted with selection %0").arg(currentSelection);
    emit unselectAll();
    currentSelection = currentSelection % (cl->m_items.length());
    dynamic_cast<ParticipantWidget*>(cl->itemAt(currentSelection)->widget())->select();
    if (timesCounted == 7) {
        gameTimer->stop();
        auto w = dynamic_cast<ParticipantWidget*>(cl->itemAt(currentSelection)->widget());
        connect(w, &ParticipantWidget::killFinished, this, &MainWindow::continueCounting);
        w->kill();
    } else {
        timesCounted = timesCounted + 1;
        currentSelection = currentSelection + 1;
    }

}
void MainWindow::continueCounting() {
    //gameInfo.participants.removeAt(currentSelection);
     cl->itemAt(currentSelection)->widget()->deleteLater();
    timesCounted = 1;
    round = round + 1;

    //currentSelection = currentSelection + 1;
    gameTimer->start();

}
MainWindow::~MainWindow()
{
    delete ui;
}

