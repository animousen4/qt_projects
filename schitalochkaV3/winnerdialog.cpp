#include "winnerdialog.h"
#include "ui_winnerdialog.h"
#include "imagehelper.h"
#include "mainwindow.h"
#include <QUrl>
#include <QAudioOutput>
WinnerDialog::WinnerDialog(QWidget *parent, ParticipantInfo _pi) :
    QDialog(parent), pi(_pi),
    ui(new Ui::WinnerDialog)
{
    ui->setupUi(this);

    player = new QMediaPlayer();
    QAudioOutput * audioOutput = new QAudioOutput;
    audioOutput->setVolume(100);
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/sound/res-data/sound/win_sound.mp3"));
    player->play();

    ui->winnerNameLabel->setText(pi.studentName);
    QPixmap pm = QPixmap(ImageHelper::getAvatar(pi.imageFileName)).scaled(QSize(180, 270), Qt::KeepAspectRatio);
    ui->imageLabel->setPixmap(pm);
    ui->imageLabel->setFixedSize(pm.size());

    connect(player, &QMediaPlayer::mediaStatusChanged, this, &WinnerDialog::onMediaStatusChanged);
    connect(ui->goMenuButton, &QPushButton::clicked, this, &WinnerDialog::onGoMenuPressed);
    connect(ui->replayButton, &QPushButton::clicked, this, &WinnerDialog::onReplayPressed);
}
void WinnerDialog::onMediaStatusChanged(QMediaPlayer::MediaStatus status) {
    qDebug() << status;
}
void WinnerDialog::closeEvent (QCloseEvent *event){
    player->pause();
    if (event->spontaneous())
        dynamic_cast<MainWindow*>(this->parent())->selectVariant(GameStatus::menuSelected);
}

void WinnerDialog::onReplayPressed() {
    dynamic_cast<MainWindow*>(this->parent())->selectVariant(GameStatus::replaySelected);
    close();
    //close();

}
void WinnerDialog::onGoMenuPressed() {
    dynamic_cast<MainWindow*>(this->parent())->selectVariant(GameStatus::menuSelected);
    close();
}
WinnerDialog::~WinnerDialog()
{
    delete ui;
}
