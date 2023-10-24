#include "windialog.h"
#include "ui_windialog.h"

WinDialog::WinDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinDialog)
{
    ui->setupUi(this);

    this->setFixedSize(size());
    connect(ui->menuButton, &QPushButton::clicked, this, [this](){
        emit goMenu();
    });

    connect(ui->restartButton, &QPushButton::clicked, this, [this](){
        emit restart();
    });
}
void WinDialog::closeEvent (QCloseEvent *event){
    parentWidget()->close();
}
WinDialog::~WinDialog()
{
    delete ui;
}
