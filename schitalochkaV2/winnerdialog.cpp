#include "winnerdialog.h"
#include "ui_winnerdialog.h"

WinnerDialog::WinnerDialog(QWidget *parent, ParticipantInfo _pi) :
    QDialog(parent), pi(_pi),
    ui(new Ui::WinnerDialog)
{
    ui->setupUi(this);
    ui->winnerNameLabel->setText(pi.studentName);
    ui->imageLabel->setPixmap(QPixmap(pi.imageFileName).scaled(QSize(200, 270), Qt::KeepAspectRatio));
    ui->wreathLabel->setPixmap(QPixmap(":/img/res/wreath.png").scaled(QSize(200, 270), Qt::KeepAspectRatio));
}

WinnerDialog::~WinnerDialog()
{
    delete ui;
}
