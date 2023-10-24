#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector.h>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void update();

private:
    Ui::MainWindow *ui;
    QTimer* timer;
    QLabel* ded;

    Vector* resistF;
    Vector* pushF;
    Vector* cursorF;
    Vector* velocity;
    Vector* acceleration;
    Vector* targetPosition;
    Vector* mousePosition;

    double radius;
    double mass;
    double nuge;
    double maxVelocity = 400;
    int cnt_clicked = 0;


protected:
    void mouseMoveEvent(QMouseEvent*) override;
    void paintEvent(QPaintEvent*) override;
};
#endif // MAINWINDOW_H
