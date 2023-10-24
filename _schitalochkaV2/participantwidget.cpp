#include "participantwidget.h"
#include <QPixmap>
#include <QPropertyAnimation>
#include <QImage>
ParticipantWidget::ParticipantWidget(ParticipantInfo _participantInfo, int _index)
    : QWidget{nullptr}, participantInfo(_participantInfo), index(_index)
{
    isAlive = true;
    isSelected = false;
    QVBoxLayout * layout = new QVBoxLayout();
    statusLabel = new QLabel("[Alive]");
    imageLabel = new QLabel();
    pm = QPixmap(participantInfo.imageFileName).scaled(QSize(80,170), Qt::KeepAspectRatio);
    imageLabel->setPixmap(pm);


    QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect();
    effect->setColor(Qt::gray);  // set the target color to gray
    effect->setStrength(0.0);    // start with zero saturation


    imageLabel->setGraphicsEffect(effect);
    animation = new QPropertyAnimation(effect, "strength");
    animation->setDuration(1000);  // set the animation duration in milliseconds
    animation->setStartValue(0.0);  // start with full saturation (colorful)
    animation->setEndValue(1.0);  // end with zero saturation (black and white)

    connect(animation, &QPropertyAnimation::finished, [this](){
        qDebug() << "Kill finished";
        emit killFinished();
    });

    layout->addWidget(new QLabel(participantInfo.studentName));
    layout->addWidget(statusLabel);
    layout->addWidget(imageLabel);

    this->setLayout(layout);
}

void ParticipantWidget::kill() {
    isAlive = false;
    statusLabel->setText("[Dead]");
    animation->start();

    // .......
}

void ParticipantWidget::select() {
    //qDebug() << QString("Selecting %0 on participant ");
    isSelected = true;
    imageLabel->setStyleSheet("border: 2px solid green;");

//    isSelected = index == watchIndex;
//    if (isSelected) {
//        qDebug() << QString("Selecting %0 on participant %1").arg(index).arg(participantInfo.studentName);
//        imageLabel->setStyleSheet("border: 2px solid green;");
//        //statusLabel->setText("FFF");

//        //imageLabel->setStyle
//    } else {
//        imageLabel->setStyleSheet("");
//        //statusLabel->setText("GGG");;
//    }
//    imageLabel->adjustSize();
}

void ParticipantWidget::unselect() {
    isSelected = false;
    imageLabel->setStyleSheet("");
}


