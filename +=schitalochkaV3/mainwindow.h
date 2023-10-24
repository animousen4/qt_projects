#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "participantwidget.h"
#include "participantinfo.h"
#include <QList>
#include "gameinfo.h"
#include <QTimer>
#include "circularlayout.h"
#include "CountingManager.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class GameStatus {
public:
    static const int ok = 0;
    static const int playing = 1;
    static const int finished = 2;
    static const int replaySelected = 3;
    static const int menuSelected = 4;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent, GameInfo _gameInfo);
    ~MainWindow();


    void selectVariant(int i) {
        gameStatus = i;
        emit gameStatusChanged(i);
    }
    void closeEvent (QCloseEvent *event);
public slots:
    void start();
    void timerEmitted();
    void continueCounting();

signals:
    void select();
    void unselectAll();
    void gameStatusChanged(int gameStatus);
private:

    int gameStatus;
    GameInfo gameInfo;
    int round;
    CircularLayout * cl;
    int currentSelection;
    int timesCounted;

    QList<QString> words;
    int curWordIndex;

    QTimer * gameTimer;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
