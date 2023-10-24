#include "menudialog.h"
#include "ui_menudialog.h"

MenuDialog::MenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuDialog)
{
    ui->setupUi(this);
    settingManager = new SettingManager();
    connect(ui->settingsButton, &QPushButton::clicked, this, &MenuDialog::openSettings);
    connect(ui->startButton, &QPushButton::clicked, this, &MenuDialog::openGame);

}

MenuDialog::~MenuDialog()
{
    delete ui;
}
