#include "participantwidget.h"
#include "imagehelper.h"
#include <QPixmap>
#include <QPropertyAnimation>
#include <QImage>
#include <QMediaPlayer>
#include <QAudioOutput>>
ParticipantWidget::ParticipantWidget(ParticipantInfo _participantInfo, int _index)
    : QWidget{nullptr}, participantInfo(_participantInfo), index(_index)
{
    isAlive = true;
    isSelected = false;
    QVBoxLayout * layout = new QVBoxLayout();
    imageLabel = new QLabel();
    wordLabel = new QLabel();
    wordLabel->setStyleSheet("font-size: 14px; font-weight: bold;");

    pm = QPixmap(ImageHelper::getAvatar(participantInfo.imageFileName)).scaled(QSize(62,108), Qt::KeepAspectRatio);
    imageLabel->setPixmap(pm);
    imageLabel->setFixedSize(pm.size());


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

    QLabel * pName = new QLabel(participantInfo.studentName);
    pName->setStyleSheet("font-size: 12px; font-style: italic");
    layout->addWidget(pName);
    layout->addWidget(imageLabel);
    layout->addWidget(wordLabel);

    this->setLayout(layout);
}

void ParticipantWidget::kill() {
    isAlive = false;
    animation->start();
    QMediaPlayer * player = new QMediaPlayer();
    QAudioOutput * audioOutput = new QAudioOutput;
    audioOutput->setVolume(100);
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/sound/res-data/sound/kill_sound.mp3"));
    player->play();

    // .......
}

void ParticipantWidget::select(QString word) {
    //qDebug() << QString("Selecting %0 on participant ");
    wordLabel->setText(word);
    isSelected = true;
    imageLabel->setStyleSheet("border: 2px solid green");
    //imageLabel->setStyleSheet("outline: 2px solid red; padding: 2px");
    //imageLabel->setStyleSheet("outline-style: solid; outline-color: green; outline-width: 2px");
}

void ParticipantWidget::unselect() {
    isSelected = false;
    imageLabel->setStyleSheet("");
    wordLabel->setText("");
}


