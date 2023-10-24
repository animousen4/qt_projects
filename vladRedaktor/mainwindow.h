#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "filewindow.h"
#include "editwindow.h"
#include "helpwindow.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_triggered();

    void on_action_2_triggered();

    void on_actionHelp_triggered();

private:
    Ui::MainWindow *ui;
    filewindow *fwindow;
    editwindow *ewindow;
    helpwindow *hwindow;
};
#endif // MAINWINDOW_H
