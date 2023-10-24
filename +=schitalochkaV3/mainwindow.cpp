#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "winnerdialog.h"
MainWindow::MainWindow(QWidget *parent, GameInfo _gameInfo)
    : QMainWindow(parent), gameInfo(_gameInfo)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gameStatus = GameStatus::ok;

    if (gameInfo.participantStartNumber != -1) {
        currentSelection = gameInfo.participantStartNumber;
    }
    round = 0;
    timesCounted = 1;

    QVBoxLayout * vb = new QVBoxLayout(this);

    cl = new CircularLayout(nullptr, 270);
    int i = 0;
    for (auto p : gameInfo.participants) {
        auto pw = new ParticipantWidget(p, i);
        connect(this, &MainWindow::unselectAll, pw, &ParticipantWidget::unselect);
        cl->addWidget(pw);
        i = i + 1;
    }
    QLabel * lab = new QLabel(gameInfo.countings[gameInfo.countingNumber]);
    CountingManager cm;

    if (gameInfo.countingNumber != -1) {
        cm = CountingManager(gameInfo.countings[gameInfo.countingNumber]);
    }

    words = cm.getWords();
    qDebug() << gameInfo.countings[gameInfo.countingNumber] << words.length() << words;

    gameTimer = new QTimer;
    gameTimer->setInterval(600);
    //gameTimer->setSingleShot(true);
    connect(gameTimer, &QTimer::timeout, this, &MainWindow::timerEmitted);


    vb->addWidget(lab);
    vb->addLayout(cl);
    ui->centralwidget->setLayout(vb);

    //c->kill();
}
void MainWindow::start() {
//    dynamic_cast<ParticipantWidget*>(cl->itemAt(currentSelection)->widget())->select(currentSelection);
//    timesCounted = timesCounted + 1;
    gameStatus = GameStatus::playing;
    emit gameStatusChanged(GameStatus::playing);
    gameTimer->start();
}
void MainWindow::closeEvent (QCloseEvent *event){
    if (event->spontaneous()) {
        gameStatus = GameStatus::menuSelected;
        qDebug() << "Closing and stopping game...";
        gameTimer->stop();
        //gameTimer->deleteLater();
        emit gameStatusChanged(GameStatus::menuSelected);
    }
}
void MainWindow::timerEmitted() {
    if (gameStatus != GameStatus::playing) {
        gameTimer->stop();
    }
    if (cl->m_items.length() == 1) {
        gameTimer->stop();
        // game finished
        WinnerDialog * wd = new WinnerDialog(this, dynamic_cast<ParticipantWidget*>(cl->itemAt(0)->widget())->getParticipantInfo());
        gameStatus = GameStatus::finished;
        emit gameStatusChanged(GameStatus::finished);
        wd->show();
        return;
    }
    qDebug () << QString("Timer emitted with selection %0").arg(currentSelection);
    emit unselectAll();
    currentSelection = currentSelection % (cl->m_items.length());
    dynamic_cast<ParticipantWidget*>(cl->itemAt(currentSelection)->widget())->select(words[timesCounted - 1]);
    ///!!!!!!
    if (timesCounted == words.length()) {
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

