#ifndef MAINWINDOWBLOC_H
#define MAINWINDOWBLOC_H

#include <QObject>
#include <QDebug>
#include "QMainWindow"
#include <QString>
#include "filepickerdialog.h"
class MainWindowBloc : public QObject
{
    Q_OBJECT
public:
    MainWindowBloc(QMainWindow *parent = nullptr) : QObject{parent} {
        filePath = "";
    }

    QString filePath;

signals:



#endif // MAINWINDOWBLOC_H
