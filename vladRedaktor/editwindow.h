#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QDialog>

namespace Ui {
class editwindow;
}

class editwindow : public QDialog
{
    Q_OBJECT

public:
    explicit editwindow(QWidget *parent = nullptr);
    ~editwindow();

private slots:
    void on_pushButton_clicked();

    void on_test_cursorPositionChanged();

private:
    Ui::editwindow *ui;
};

#endif // EDITWINDOW_H
