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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent, GameInfo _gameInfo);
    ~MainWindow();
public slots:
    void start();
    void timerEmitted();
    void continueCounting();

signals:
    void select();
    void unselectAll();
private:

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
