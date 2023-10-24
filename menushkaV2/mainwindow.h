#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QFile>
#include<fstream>
#include<sstream>
#include<string>
#include <QCloseEvent>
#include "statcollectordialog.h"
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QString currentEditText;
    QString fileName;

    QTextEdit* fileNameEdit;
    QTextEdit* textEdit;
    StatCollectorDialog* curDialog;
    QMenu* editMenu;
    QString readFileFromString();

    fstream fileIO;


public slots:
    void calculate();
    void save();
    void onLabelHelp(const QString & link);
    QString load();
};
#endif // MAINWINDOW_H
