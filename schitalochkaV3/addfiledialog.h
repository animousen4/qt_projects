#ifndef ADDFILEDIALOG_H
#define ADDFILEDIALOG_H

#include <QDialog>
#include "settingmanager.h"
namespace Ui {
class AddFileDialog;
}

class AddFileDialog : public QDialog
{
    Q_OBJECT

public:
    // 0 - countings; 1 - participant
    explicit AddFileDialog(QWidget *parent = nullptr, SettingManager * _settingManager = nullptr, int _type = 0);
    ~AddFileDialog();

public slots:
    void onFileNameEdit();
    void onAddButtonPressed();
private:
    Ui::AddFileDialog *ui;
    SettingManager * settingManager;
    int type;
};

#endif // ADDFILEDIALOG_H
