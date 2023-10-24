#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <QDialog>
#include "settingsdialog.h"
#include "settingmanager.h"
#include "mainwindow.h"
#include <QStringListModel>
#include "addfiledialog.h"
#include "preset.h"
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
        mw = new MainWindow(nullptr, *settingManager->gameInfo);
        connect(mw, &MainWindow::gameStatusChanged, this, &MenuDialog::onGameStatusChanged);
        mw->show();
        this->hide();
        mw->start();
    }
    void onOpenParticipantsFile() {
        AddFileDialog * d = new AddFileDialog(this, settingManager, 1);
        d->show();
    }
    void onOpenCountingsFile() {
        AddFileDialog * d = new AddFileDialog(this, settingManager, 0);
        d->show();
    }
    void onGameStatusChanged(int gameStatus) {
        switch (gameStatus) {
        case GameStatus::menuSelected:
            mw->close();
            this->show();
            break;
        case GameStatus::replaySelected:
            mw->close();
            mw = new MainWindow(this, *settingManager->gameInfo);
            connect(mw, &MainWindow::gameStatusChanged, this, &MenuDialog::onGameStatusChanged);
            mw->show();
            mw->start();
            break;
        default:
            break;
        }
    }
    void onGameInfoChanged();
private:
    Ui::MenuDialog *ui;
    MainWindow * mw;
    QStringListModel * participantsModel;
    QStringListModel * countingsModel;
};

#endif // MENUDIALOG_H
