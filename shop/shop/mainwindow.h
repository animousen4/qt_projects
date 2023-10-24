#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "abstractclass.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    abstractClass *a1, *a2, *a3, *b1, *b2, *b3;

public slots:
    void openFiles();
    void sortSets();
    void mergeSets();
    void findSmth();

    void sortBags();
    void mergeBags();

private:
    Ui::MainWindow *ui;
    void updateTables();
};
#endif // MAINWINDOW_H
