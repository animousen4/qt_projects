#include "addparticipantdialog.h"
#include "ui_addparticipantdialog.h"
#include <QFile>
#include "participantinfo.h"
AddParticipantDialog::AddParticipantDialog(QWidget *parent, SettingManager * _settingManager) :
    QDialog(parent), settingManager(_settingManager),
    ui(new Ui::AddParticipantDialog)
{
    ui->setupUi(this);
    connect(ui->addButton, &QPushButton::clicked, this, &AddParticipantDialog::onAddPressed);
    connect(ui->fileNameEdit, &QLineEdit::textEdited, this, &AddParticipantDialog::onFileNameChanged);
    onFileNameChanged();
}
void AddParticipantDialog::onAddPressed() {
    settingManager->addParticipant(ParticipantInfo(ui->participantNameEdit->text(), ui->fileNameEdit->text()));
    this->close();
}
void AddParticipantDialog::onFileNameChanged() {
    QFile f(ui->fileNameEdit->text());
    f.open(QFile::ReadOnly);
    if (ui->fileNameEdit->text() != "") {
        if (f.isOpen()) {
            ui->addButton->setDisabled(false);
            ui->validatorLabel->setText("");
        } else {

            ui->addButton->setDisabled(true);
            ui->validatorLabel->setText("File not exists");
        }
    } else {
        ui->addButton->setDisabled(false);
        ui->validatorLabel->setText("");
    }

}
AddParticipantDialog::~AddParticipantDialog()
{
    delete ui;
}
