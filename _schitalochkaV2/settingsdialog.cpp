#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QStringListModel>
SettingsDialog::SettingsDialog(QWidget *parent, SettingManager * _settingManager) :
    QDialog(parent), settingManager(_settingManager),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    participantsModel = new QStringListModel(this);
    connect(settingManager, &SettingManager::gameInfoChanged, this, &SettingsDialog::onGameInfoChanged);
    connect(ui->addParticipant, &QPushButton::clicked, this, &SettingsDialog::onAddParticipantClicked);
    connect(ui->removeParticipant, &QPushButton::clicked, this, &SettingsDialog::onRemoveParticipantClicked);
    //connect(participantsModel, &QStringListModel::)
    onGameInfoChanged();
    //settingManager->gameInfo.
}
void SettingsDialog::onGameInfoChanged() {
    QList<QString> participants;
    qDebug() << "Participants amount: " << settingManager->gameInfo->participants.length();
    for (auto p : settingManager->gameInfo->participants) {
        participants.push_back(QString("%0 [%1]").arg(p.studentName).arg(p.imageFileName));
    }
    participantsModel->setStringList(participants);
    ui->participantsListView->setModel(participantsModel);
}

void SettingsDialog::onAddParticipantClicked() {
    settingManager->addParticipant(ParticipantInfo("Guga fd", "f.png"));
}
void SettingsDialog::onRemoveParticipantClicked(){

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
