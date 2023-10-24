#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <QDialog>
#include "settingsdialog.h"
#include "settingmanager.h"
#include "mainwindow.h"
#include <QStringListModel>
namespace Ui {
class MenuDialog;
}

class MenuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MenuDialog(QWidget *parent = nullptr);
    SettingManager * settingManager;
    ~MenuDialog();
public slots:
    void openSettings() {
        SettingsDialog * sd = new SettingsDialog(this, settingManager);
        sd->show();
    }
    void openGame() {
        MainWindow * mw = new MainWindow(this, *settingManager->gameInfo);
        mw->show();
        mw->start();
    }
    void onGameInfoChanged();
private:
    Ui::MenuDialog *ui;
    QStringListModel * participantsModel;
    QStringListModel * countingsModel;
};

#endif // MENUDIALOG_H
