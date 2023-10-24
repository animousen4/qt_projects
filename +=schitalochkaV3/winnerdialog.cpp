#include "winnerdialog.h"
#include "ui_winnerdialog.h"
#include "imagehelper.h"
#include "mainwindow.h"
WinnerDialog::WinnerDialog(QWidget *parent, ParticipantInfo _pi) :
    QDialog(parent), pi(_pi),
    ui(new Ui::WinnerDialog)
{
    ui->setupUi(this);
    ui->winnerNameLabel->setText(pi.studentName);
    ui->imageLabel->setPixmap(QPixmap(ImageHelper::getAvatar(pi.imageFileName)).scaled(QSize(200, 270), Qt::KeepAspectRatio));


    connect(ui->goMenuButton, &QPushButton::clicked, this, &WinnerDialog::onGoMenuPressed);
    connect(ui->replayButton, &QPushButton::clicked, this, &WinnerDialog::onReplayPressed);
}
void WinnerDialog::closeEvent (QCloseEvent *event){
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
