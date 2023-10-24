#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QMainWindow>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class HomeWindow; }
QT_END_NAMESPACE

class HomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    HomeWindow(QWidget *parent = nullptr);
    ~HomeWindow();

private slots:
    void shotTimer();
private:
    Ui::HomeWindow *ui;
    QTimer *timer;
    double k;
};
#endif // HOMEWINDOW_H
