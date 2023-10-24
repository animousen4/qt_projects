#include "addcountingdialog.h"
#include "./ui_addcountingdialog.h"

AddCountingDialog::AddCountingDialog(QWidget *parent, SettingManager * manager) :
    QDialog(parent), settingManager(manager),
    ui(new Ui::AddCountingDialog)
{
    ui->setupUi(this);
    ui->addCountingButton->setDisabled(true);
    connect(ui->addCountingButton, &QPushButton::clicked, this, &AddCountingDialog::onAddPressed);
    connect(ui->countingEdit, &QLineEdit::textEdited, this, &AddCountingDialog::onEditCounting);
}
void AddCountingDialog::onAddPressed() {
    settingManager->addCounting(ui->countingEdit->text());
    this->close();
}

void AddCountingDialog::onEditCounting(){
    QString text = ui->countingEdit->text();
    bool has;
    has = settingManager->isExistCounting(text);

    if (text.isEmpty()) {
        ui->addCountingButton->setDisabled(true);
        ui->validatorLabel->setText("");
    } else {
        ui->addCountingButton->setDisabled(has);
        if (has) {
            ui->validatorLabel->setText("Такая считалочка уже существует");
        } else {
            ui->validatorLabel->setText("");
        }

    }
}
AddCountingDialog::~AddCountingDialog()
{
    delete ui;
}
