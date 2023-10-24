#ifndef WINDIALOG_H
#define WINDIALOG_H

#include <QDialog>
#include <QCloseEvent>
namespace Ui {
class WinDialog;
}

class WinDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WinDialog(QWidget *parent = nullptr);
    ~WinDialog();

protected:
    void closeEvent (QCloseEvent *event) override;
signals:
    void goMenu();
    void restart();
private:
    Ui::WinDialog *ui;
};

#endif // WINDIALOG_H
