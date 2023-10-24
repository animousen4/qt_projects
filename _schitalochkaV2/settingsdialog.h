#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "settingmanager.h"
#include <QStringListModel>
namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr, SettingManager * _settingManager = nullptr);
    ~SettingsDialog();

private:
    Ui::SettingsDialog *ui;
    SettingManager * settingManager;
    QStringListModel * participantsModel;
public slots:
    void onGameInfoChanged();
    void onAddParticipantClicked();
    void onRemoveParticipantClicked();
};

#endif // SETTINGSDIALOG_H
