#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QDebug>
#include "gamesettings.h"
#include "targetwidget.h"
#include "windialog.h"
#include <QMediaPlayer>
QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

enum GameStatus {
    playing,
    win,
    stop
};
class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent, GameSettings gameSettings, bool _drawVec);
    ~GameWindow();

public slots:
    void onTimerEmit();
    void onTargetHit();
protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::GameWindow *ui;
    GameWindow* restartGame();
    TargetWidget * targetWidget;
    QTimer * timer;
    Vec2D cursorPos;
    Vec2D prevCursorPos;
    Vec2D mouseMoveVec;
    GameSettings gameSettings;
    GameStatus gameStatus;
    QMediaPlayer* player;
    QLabel * kataf;
    void paintEvent(QPaintEvent *event) override;

    int distance;

    bool drawVec;
    bool curDrawVec;
    bool isInWindow();
    // s
    double time;

    void startDeathProcess();
    void drawOneVec(QPainter* painter, QColor color, Vec2D p);

};
#endif // GAMEWINDOW_H
