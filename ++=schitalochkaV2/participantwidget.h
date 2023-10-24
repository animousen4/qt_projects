#ifndef PARTICIPANTWIDGET_H
#define PARTICIPANTWIDGET_H

#include <QWidget>
#include "participantinfo.h"
#include <QtWidgets>
class ParticipantWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParticipantWidget(ParticipantInfo _participantInfo, int _index);

private:
    ParticipantInfo participantInfo;
    QLabel * statusLabel;
    QLabel * imageLabel;
    QPropertyAnimation *animation;
    QPixmap pm;

    int index;
    bool isSelected;
    bool isAlive;
signals:
    void killFinished();

public slots:
    void kill();
    void select();
    void unselect();
};

#endif // PARTICIPANTWIDGET_H
