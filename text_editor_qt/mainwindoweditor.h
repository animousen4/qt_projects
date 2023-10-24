#ifndef MAINWINDOWEDITOR_H
#define MAINWINDOWEDITOR_H

#include <QMainWindow>
#include <QWidget>
#include <string>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowEditor; }
QT_END_NAMESPACE

class MainWindowEditor : public QMainWindow
{
    Q_OBJECT

public:
    MainWindowEditor(QWidget *parent = nullptr);
    ~MainWindowEditor();

    void setFile(QString s) {
        file = s;
        return;
    }

    QString getFile() {
        return file;
    }

    void assess();

public slots:
    //void on_pushButton_clicked();

    //void on_lineEdit_editingFinished();

    //void on_inputThing_editingFinished();

    void on_inputThing_returnPressed();

    //void enteredFileName();

    void on_textEditor_textChanged();

private:
    Ui::MainWindowEditor *ui;
    QString file;

    int countWords(QString, int*);
    bool ifDivider(QChar x){
        return (x == '.' || x == ',' || x == ' ' || x == '!' || x == '?' || x == ':' || x == ';' || x == '(' || x == ')' || x == '{' || x == '}' || x == '[' || x == ']');
    }

    void sortSYmbolsByFrequency(int*, QChar*, int);
};
#endif // MAINWINDOWEDITOR_H
