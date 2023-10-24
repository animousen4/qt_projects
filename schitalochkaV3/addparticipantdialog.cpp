#include "addparticipantdialog.h"
#include "ui_addparticipantdialog.h"
#include <QFile>
#include "participantinfo.h"
AddParticipantDialog::AddParticipantDialog(QWidget *parent, SettingManager * _settingManager) :
    QDialog(parent), settingManager(_settingManager),
    ui(new Ui::AddParticipantDialog)
{
    ui->setupUi(this);
    ui->addButton->setDisabled(true);
    connect(ui->addButton, &QPushButton::clicked, this, &AddParticipantDialog::onAddPressed);
    connect(ui->fileNameEdit, &QLineEdit::textEdited, this, &AddParticipantDialog::onFileNameChanged);
    connect(ui->participantNameEdit, &QLineEdit::textEdited, this, &AddParticipantDialog::onParticipantNameChanged);
    onFileNameChanged();
}
void AddParticipantDialog::validate() {
    bool isValid;

    QFile f(ui->fileNameEdit->text());
    if (ui->fileNameEdit->text() != "") {
        f.open(QFile::ReadOnly);
        if (f.isOpen()) {
            //ui->addButton->setDisabled(false);
            ui->validatorLabel->setText("");
            isValid = true;

            f.close();
        } else {

            //ui->addButton->setDisabled(true);
            ui->validatorLabel->setText("Такого файла не существует");
            isValid = false;
        }
    } else {
        //ui->addButton->setDisabled(false);
        ui->validatorLabel->setText("");
        isValid = true;
    }


    if (settingManager->hasParticipant(ui->participantNameEdit->text())) {
        ui->validatorLabel->setText("Такой участник уже есть");
        isValid = false;
    } else {
        isValid = isValid && !ui->participantNameEdit->text().isEmpty();
    }

    ui->addButton->setEnabled(isValid);
}
void AddParticipantDialog::onAddPressed() {
    settingManager->addParticipant(ParticipantInfo(ui->participantNameEdit->text(), ui->fileNameEdit->text()));
    this->close();
}
void AddParticipantDialog::onParticipantNameChanged() {
    validate();
}
void AddParticipantDialog::onFileNameChanged() {
    validate();
}
AddParticipantDialog::~AddParticipantDialog()
{
    delete ui;
}
