#ifndef TARGETWIDGET_H
#define TARGETWIDGET_H

#include <QWidget>
#include <targetphysics.h>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <targetprops.h>
#include "clickablelabel.h"
#include "vec.h"
class TargetWidget : public QWidget
{
    Q_OBJECT

private:
    TargetPhysics * targetPhysics;
    TargetProps * targetProps;
    ClickableLabel * targetImage;
    int triggerRadius;
public:
    TargetWidget(QWidget *parent, TargetPhysics _targetPhysics, TargetProps _targetProps, int _triggerRadius) :
        QWidget{parent},
        targetPhysics(new TargetPhysics(_targetPhysics)), targetProps(new TargetProps(_targetProps)), triggerRadius(_triggerRadius){

        QVBoxLayout * layout = new QVBoxLayout;

        //this->setAttribute(Qt::WA_TransparentForMouseEvents);
        targetImage = new ClickableLabel(this);
        targetImage->setPixmap(QPixmap(targetProps->getImage()).scaled(targetProps->picSize.toQSize()));
        targetImage->setFixedSize(targetImage->pixmap().size());
        this->setFixedSize(targetImage->pixmap().size());
        layout->addWidget(targetImage);

        connect(targetImage, &ClickableLabel::clicked, this, &TargetWidget::onImageClick);
        this->setLayout(layout);
    }


    void updatePos(double t) {
        targetPhysics->update(t);
        //qDebug() <<*targetPhysics;
        this->move((targetPhysics->getPos() - targetProps->picSize / 2).toQPoint());
    }
    void changeTargetPhysics(TargetPhysics _targetPhysics) {
        delete targetPhysics;
        targetPhysics = new TargetPhysics(_targetPhysics);
    }

    ClickableLabel* getTargetImage(){
        return targetImage;
    }


    int getTriggerRadius() {
        return triggerRadius;
    }

    TargetPhysics* getTargetPhysics() {
        return targetPhysics;
    }

    TargetProps * getTargetProps(){
        return targetProps;
    }

    // pos of phys center
    Vec2D getPos() {
        return targetPhysics->getPos(); //Vec2D{this->pos().x(), this->pos().y()};
    }

    bool isTriggered(Vec2D cursor) {
        return triggerRadius > cursor.distance(getPos());
    }

public slots:
    void onImageClick() {
        emit hit();
    }
signals:
    void hit();
};

#endif // TARGETWIDGET_H
