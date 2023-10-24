#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "settingmanager.h"
#include <QStringListModel>
#include <QItemSelectionModel>
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
    QStringListModel * countingsModel;
public slots:
    void onGameInfoChanged();
    void onAddParticipantClicked();
    void onRemoveParticipantClicked();
    void onParticipantSelected(const QItemSelection &selected, const QItemSelection &deselected);
    //void onCountingSelected(const QItemSelection &selected, const QItemSelection &deselected);
};

#endif // SETTINGSDIALOG_H
