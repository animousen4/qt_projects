#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QStringListModel>
#include "addparticipantdialog.h"
#include "addcountingdialog.h"
#include "preset.h"
SettingsDialog::SettingsDialog(QWidget *parent, SettingManager * _settingManager) :
    QDialog(parent), settingManager(_settingManager),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->participantValidatorLabel->setText("");
    ui->countingValidatorLabel->setText("");
    ui->removeCounter->setDisabled(true);
    ui->participantsListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->countersListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->removeParticipant->setDisabled(true);

    participantsModel = new QStringListModel(this);
    countingsModel = new QStringListModel(this);

    ui->countersListView->setModel(countingsModel);
    ui->participantsListView->setModel(participantsModel);

    connect(settingManager, &SettingManager::gameInfoChanged, this, &SettingsDialog::onGameInfoChanged);
    connect(ui->addParticipant, &QPushButton::clicked, this, &SettingsDialog::onAddParticipantClicked);
    connect(ui->removeParticipant, &QPushButton::clicked, this, &SettingsDialog::onRemoveParticipantClicked);
    connect(ui->participantsListView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &SettingsDialog::onParticipantSelected);
    connect(ui->addCounter, &QPushButton::clicked, this, &SettingsDialog::onAddCountingClicked);
    connect(ui->removeCounter, &QPushButton::clicked, this, &SettingsDialog::onRemoveCountingClicked);
    connect(ui->countersListView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &SettingsDialog::onCountingSelected);
    connect(ui->participantStartNumberEdit, &QLineEdit::textChanged, this, &SettingsDialog::onStartParticipantChanged);
    connect(ui->isRandomParticipantCheckBox, &QCheckBox::clicked, this, &SettingsDialog::onPressRandomParticipant);
    connect(ui->isRandomCountingCheckBox, &QCheckBox::clicked, this, &SettingsDialog::onPressRandomCounting);
    connect(ui->countingNumberEdit, &QLineEdit::textChanged, this, &SettingsDialog::onCountingNumberChanged);
    onGameInfoChanged();

}

void SettingsDialog::onPressRandomParticipant(bool isRandom) {
    settingManager->changeParticipantStartNumber(isRandom ? -1 : 0);
}
void SettingsDialog::onPressRandomCounting(bool isRandom) {
    settingManager->changeCountingNumber(isRandom ? -1 : 0);
}
void SettingsDialog::onGameInfoChanged() {
    QList<QString> participants;
    qDebug() << "Participants amount: " << settingManager->gameInfo->participants.length();
    for (auto p : settingManager->gameInfo->participants) {
        participants.push_back(QString("%0 [%1]").arg(p.studentName).arg(p.imageFileName));
    }
    QList<QString> countings;
    for (auto p : settingManager->gameInfo->countings) {
        countings.push_back(p);
    }
    countingsModel->setStringList(countings);
    participantsModel->setStringList(participants);
    if (settingManager->gameInfo->participants.isEmpty()) {
        ui->participantStartNumberEdit->setDisabled(true);
        ui->isRandomParticipantCheckBox->setDisabled(true);
        ui->participantStartNumberEdit->setText("");
        ui->participantValidatorLabel->setText("");
    } else {
        ui->isRandomParticipantCheckBox->setDisabled(false);
        if (settingManager->gameInfo->participantStartNumber != -1) {
            ui->participantStartNumberEdit->setDisabled(false);
            ui->isRandomParticipantCheckBox->setChecked(false);
            ui->participantStartNumberEdit->setText(QString::number(settingManager->gameInfo->participantStartNumber+1));
        } else {
            ui->isRandomParticipantCheckBox->setChecked(true);
            ui->participantStartNumberEdit->setText("");
            ui->participantStartNumberEdit->setDisabled(true);
        }
    }

    if (settingManager->gameInfo->countings.isEmpty()) {
        ui->countingNumberEdit->setDisabled(true);
        ui->isRandomCountingCheckBox->setDisabled(true);
        ui->countingNumberEdit->setText("");
        ui->countingValidatorLabel->setText("");
    } else {
        ui->isRandomCountingCheckBox->setDisabled(false);
        if (settingManager->gameInfo->countingNumber != -1) {
            ui->isRandomCountingCheckBox->setChecked(false);
            ui->countingNumberEdit->setDisabled(false);
            ui->countingNumberEdit->setText(QString::number(settingManager->gameInfo->countingNumber+1));
        } else {
            ui->isRandomCountingCheckBox->setChecked(true);
             ui->countingNumberEdit->setText("");
            ui->countingNumberEdit->setDisabled(true);
        }
    }


}
void SettingsDialog::onAddCountingClicked() {
    AddCountingDialog * addCountingDialog = new AddCountingDialog(this, settingManager);
    addCountingDialog->show();
}
void SettingsDialog::onAddParticipantClicked() {

    //settingManager->addParticipant(ParticipantInfo("Guga fd", "f.png"));
    AddParticipantDialog * d = new AddParticipantDialog(this, settingManager);
    d->show();
}
void SettingsDialog::onParticipantSelected(const QItemSelection &selected, const QItemSelection &deselected) {
    if (selected.indexes().isEmpty()) {
        ui->removeParticipant->setDisabled(true);
    } else {
        ui->removeParticipant->setDisabled(false);
    }
    //qDebug() << selected.indexes().first().;
}

void SettingsDialog::onStartParticipantChanged() {
    if (ui->participantStartNumberEdit->text().isEmpty()) {
        if (settingManager->gameInfo->participantStartNumber != -1)
            ui->participantValidatorLabel->setText("Поле не должно быть пустым");
    } else {
    int num = ui->participantStartNumberEdit->text().toInt();
    if (num > 0 && num <= settingManager->gameInfo->participants.length()) {
        ui->participantValidatorLabel->setText("");
        settingManager->changeParticipantStartNumber(num-1);
    } else {
        ui->participantValidatorLabel->setText("Участника с таким номером не существует!");
    }
    }
}
void SettingsDialog::onCountingNumberChanged() {
    if (ui->countingNumberEdit->text().isEmpty()) {
        if (settingManager->gameInfo->countingNumber != -1)
            ui->countingValidatorLabel->setText("Поле не должно быть пустым");
    } else {
    int num = ui->countingNumberEdit->text().toInt();
    if (num > 0 && num <= settingManager->gameInfo->countings.length()) {
        ui->countingValidatorLabel->setText("");
        settingManager->changeCountingNumber(num-1);
    } else {
        ui->countingValidatorLabel->setText("Считалочки с таким номером не существует!");
    }
    }
}
void SettingsDialog::onRemoveParticipantClicked(){
    for (auto index : ui->participantsListView->selectionModel()->selectedIndexes()) {
        settingManager->removeParticipant(index.row());
    }
    ui->removeParticipant->setDisabled(true);
}

void SettingsDialog::onRemoveCountingClicked() {
    for (auto index : ui->countersListView->selectionModel()->selectedIndexes()) {
        settingManager->removeCounting(index.row());
    }
    ui->removeCounter->setDisabled(true);
}
void SettingsDialog::onCountingSelected(const QItemSelection &selected, const QItemSelection &deselected) {

    if (selected.indexes().isEmpty()) {
        ui->removeCounter->setDisabled(true);
    } else {
        ui->removeCounter->setDisabled(false);
    }
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
