#ifndef ADDPARTICIPANTDIALOG_H
#define ADDPARTICIPANTDIALOG_H

#include <QDialog>
#include "settingmanager.h"
namespace Ui {
class AddParticipantDialog;
}

class AddParticipantDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddParticipantDialog(QWidget *parent = nullptr, SettingManager * _settingManager = nullptr);
    ~AddParticipantDialog();

public slots:
    void onAddPressed();
    void onParticipantNameChanged();
    void onFileNameChanged();
private:
    Ui::AddParticipantDialog *ui;
    SettingManager * settingManager;
    void validate();
};

#endif // ADDPARTICIPANTDIALOG_H
