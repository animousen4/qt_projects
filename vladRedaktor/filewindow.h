#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include <QDialog>

namespace Ui {
class filewindow;
}

class filewindow : public QDialog
{
    Q_OBJECT

public:
    explicit filewindow(QWidget *parent = nullptr);
    ~filewindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::filewindow *ui;
};

#endif // FILEWINDOW_H
