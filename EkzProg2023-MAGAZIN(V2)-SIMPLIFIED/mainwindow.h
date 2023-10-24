#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mcl.h>
#include <QFile>
#include <TableModels.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    ABS_COMP * s1;
    ABS_COMP * s2;
    ABS_COMP * m;

    void loadData(bool bin = false);
    void updateData();

};


#endif // MAINWINDOW_H
