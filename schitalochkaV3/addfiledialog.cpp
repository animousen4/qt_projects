#include "addfiledialog.h"
#include "ui_addfiledialog.h"
#include <QFile>
#include "participantinfo.h"
AddFileDialog:: AddFileDialog(QWidget *parent, SettingManager * _settingManager, int _type) :
    settingManager(_settingManager), type(_type),
    QDialog(parent),
    ui(new Ui::AddFileDialog)
{
    ui->setupUi(this);

    connect(ui->addButton, &QPushButton::clicked, this, &AddFileDialog::onAddButtonPressed);
    connect(ui->fileNameEdit, &QLineEdit::textEdited, this, &AddFileDialog::onFileNameEdit);
    ui->validatorLabel->setText("");
    ui->addButton->setEnabled(false);
}
void AddFileDialog::onFileNameEdit() {
    QFile file(ui->fileNameEdit->text());

    file.open(QFile::ReadOnly);

    if (file.isOpen()) {
        if (type != 0) {
            if (QTextStream(&file).readLine().split(' ').length() < 2) {
                ui->validatorLabel->setText("Неверный формат");
                ui->addButton->setEnabled(false);
            }
        }
        ui->validatorLabel->setText("");
        ui->addButton->setEnabled(true);
        file.close();
    } else {
        ui->validatorLabel->setText("Такого файла не существует");
        ui->addButton->setEnabled(false);
    }

}
void AddFileDialog::onAddButtonPressed() {
    QFile file(ui->fileNameEdit->text());
    QTextStream textStream(&file);
    file.open(QFile::ReadOnly);

    if (type == 0) {
        // countings
        QList<QString> data;
        while (!textStream.atEnd()) {
            QString line = textStream.readLine();
            if (!line.isEmpty())
                data.push_back(line);
        }
        settingManager->changeCountingsList(data);
    } else {
        // participants
        QList<ParticipantInfo> piList;
        while (!textStream.atEnd()) {
            QList<QString> fragments;
            fragments = textStream.readLine().split(' ');
            if (fragments.length() == 1 && fragments[0] == "")
                continue;
            QString fName;
            if (fragments.length() < 3) {
                fName = "";
            } else {
                fName = fragments[2];
            }
            piList.append(ParticipantInfo(fragments[0] + " " + fragments[1], fName));
        }
        settingManager->changeParticipantList(piList);
        //settingManager->changeParticipantStartNumber(-1);
    }

    file.close();
    close();
}
AddFileDialog::~AddFileDialog()
{
    delete ui;
}
