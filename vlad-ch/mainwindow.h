
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QSequentialAnimationGroup>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    unsigned short count;
    QMediaPlayer *player;
    QSequentialAnimationGroup* animationGroup;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_Start_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
