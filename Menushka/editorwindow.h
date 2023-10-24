#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

namespace Ui {
class EditorWindow;
}

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorWindow(QWidget *parent = nullptr, QString path = NULL);
    ~EditorWindow();
    QString readFileFromString();
private:
    fstream fileIO;
    QString fileName;
    Ui::EditorWindow *ui;


protected:
    void closeEvent(QCloseEvent *event);
public slots:
    void collectStat();
    void saveFile();

};

#endif // EDITORWINDOW_H
