#ifndef WINNERDIALOG_H
#define WINNERDIALOG_H

#include <QDialog>
#include "participantinfo.h"
namespace Ui {
class WinnerDialog;
}

class WinnerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WinnerDialog(QWidget *parent, ParticipantInfo _pi);
    ~WinnerDialog();

private:
    Ui::WinnerDialog *ui;
    ParticipantInfo pi;
};

#endif // WINNERDIALOG_H
