#ifndef WINDOWBLOC_H
#define WINDOWBLOC_H

#include <QObject>
#include <QDebug>
class WindowBloc : public QObject
{
    Q_OBJECT
public:
    WindowBloc();

public slots:
    void onFilePressed() {
        qDebug() << "File pressed";
    }

    void onEditPressed() {


    }
};

#endif // WINDOWBLOC_H
