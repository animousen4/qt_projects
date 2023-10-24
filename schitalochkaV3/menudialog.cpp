#include "menudialog.h"
#include "ui_menudialog.h"

MenuDialog::MenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuDialog)
{
    ui->setupUi(this);

    //auto qAct = new QAction("FFFFF");
    //ui->menubar->addAction(qAct);

    //connect(qAct, &QAction::triggered, this, ...);


    settingManager = new SettingManager();
    connect(ui->settingsButton, &QPushButton::clicked, this, &MenuDialog::openSettings);
    connect(ui->startButton, &QPushButton::clicked, this, &MenuDialog::openGame);
    connect(settingManager, &SettingManager::gameInfoChanged, this, &MenuDialog::onGameInfoChanged);

    connect(ui->openCountings, &QAction::triggered, this, &MenuDialog::onOpenCountingsFile);
    connect(ui->openParticipants, &QAction::triggered, this, &MenuDialog::onOpenParticipantsFile);

    //connect(ui->pm5group, &QAction::triggered, this, &MenuDialog::onSelectStandart5Pm);
    ui->participantsListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->countersListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    participantsModel = new QStringListModel(this);
    countingsModel = new QStringListModel(this);

    ui->countersListView->setModel(countingsModel);
    ui->participantsListView->setModel(participantsModel);

    for (auto p : StdPresets::getAllPresets()) {
        QAction * act = new QAction(p.name);
        ui->stdPresets->addAction(act);
        connect(act, &QAction::triggered, this, [this, p](){
            settingManager->changeGameInfo(p.data);
        });
    }
    onGameInfoChanged();

}
void MenuDialog::onGameInfoChanged() {
    QList<QString> participants;
    qDebug() << "Participants amount: " << settingManager->gameInfo->participants.length();
    for (auto p : settingManager->gameInfo->participants) {
        participants.push_back(QString("%0 [%1]").arg(p.studentName).arg(p.imageFileName));
    }
    QList<QString> countings;
    for (auto p : settingManager->gameInfo->countings) {
        countings.push_back(p);
    }

    bool isParticipantValid, isCountingsValid;
    if (participants.length() < 2) {
        ui->validatorLabel->setText("Необходимо как минимум 2 участника");
        isParticipantValid = false;
    } else {
        ui->validatorLabel->setText("");
        isParticipantValid = true;
    }

    if (countings.length() < 1) {
        ui->validatorLabel->setText("Необходимо как минимум 1 считалочка");
        isCountingsValid = false;
    } else {
        isCountingsValid = true;
    }

    ui->startButton->setEnabled(isParticipantValid && isCountingsValid);

    countingsModel->setStringList(countings);
    participantsModel->setStringList(participants);
}
MenuDialog::~MenuDialog()
{
    delete ui;
}
