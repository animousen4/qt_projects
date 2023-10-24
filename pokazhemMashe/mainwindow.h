#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialogfile.h"
#include "MyLayout.h"
#include "PlayerWidget.h"
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void startGame();
    void delay();

    DialogFile* dialog;
    MyLayout* main_layout;
    QTimer* timer;
    //Player* current_player;
    int cur_cnt_words;
    int index_player;

    QStringList cur_words;
    bool is_game_on = false;

public slots:
    void open_file();
    void extractName();
    void timeIsUp();

private:
    Ui::MainWindow *ui;

    int random(int, int);
};
#endif // MAINWINDOW_H
