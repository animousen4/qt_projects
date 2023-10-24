#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <QDialog>
#include "settingsdialog.h"
#include "settingmanager.h"
#include "mainwindow.h"
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
private:
    Ui::MenuDialog *ui;
};

#endif // MENUDIALOG_H
