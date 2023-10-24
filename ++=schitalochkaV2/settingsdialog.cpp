#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QStringListModel>
#include "addparticipantdialog.h"
SettingsDialog::SettingsDialog(QWidget *parent, SettingManager * _settingManager) :
    QDialog(parent), settingManager(_settingManager),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
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
    QList<QString> countings;
    for (auto p : settingManager->gameInfo->countings) {
        countings.push_back(p);
    }
    countingsModel->setStringList(countings);
    participantsModel->setStringList(participants);

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
void SettingsDialog::onRemoveParticipantClicked(){
    for (auto index : ui->participantsListView->selectionModel()->selectedIndexes()) {
        settingManager->removeParticipant(index.row());
    }
    //qDebug() << ui->participantsListView->selectionModel()->selectedIndexes();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
