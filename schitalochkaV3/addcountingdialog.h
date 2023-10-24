#ifndef ADDCOUNTINGDIALOG_H
#define ADDCOUNTINGDIALOG_H

#include <QDialog>
#include "settingmanager.h"
namespace Ui {
class AddCountingDialog;
}

class AddCountingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCountingDialog(QWidget *parent = nullptr, SettingManager * manager = nullptr);
    ~AddCountingDialog();
public slots:

    void onAddPressed();
    void onEditCounting();
private:
    Ui::AddCountingDialog *ui;
    SettingManager * settingManager;
};

#endif // ADDCOUNTINGDIALOG_H
