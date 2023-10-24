#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateEdit>
#include <qcustomplot.h>

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
    void getDate();

private:
    Ui::MainWindow *ui;
    QDateTime* date_of_birth;
    QDateTime* date_to_calculate;
    QLineEdit* date_of_birth_edit;
    QLineEdit* calculation_date_edit;
    QCustomPlot* graphics_viewer;
    void paintGraphic(int, int);

    struct Point {
        double x;
        double y;
    };
};
#endif // MAINWINDOW_H
