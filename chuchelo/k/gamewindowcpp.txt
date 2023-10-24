#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QRgb>
#include <QPropertyAnimation>
#include <QCursor>
#include <QAudioOutput>
GameWindow::GameWindow(QWidget *parent, GameSettings _gameSettings, bool _drawVec)
    : QMainWindow(parent), ui(new Ui::GameWindow), gameSettings(_gameSettings), drawVec(_drawVec), curDrawVec(_drawVec)
{
    ui->setupUi(this);

    gameStatus = playing;

    this->centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->setMouseTracking(true);
    this->setFixedSize(size());
    timer = new QTimer();
    timer->setInterval(10);

    kataf = new QLabel(this);

    kataf->setPixmap(QPixmap(gameSettings.katafImage()).scaled(200,100));
    kataf->setFixedSize(kataf->pixmap().size());
    kataf->hide();

    player = new QMediaPlayer();
    QAudioOutput * audioOutput = new QAudioOutput;
    audioOutput->setVolume(100);
    player->setAudioOutput(audioOutput);

    targetWidget = new TargetWidget(this, TargetPhysics(Vec2D{this->size().width()/2, this->size().height()/2}, gameSettings.physSettings), TargetProps(gameSettings.hp, gameSettings.images) , gameSettings.triggerRadius);
    targetWidget->updatePos(((double)timer->interval()) / 1000);

    connect(targetWidget, &TargetWidget::hit, this, &GameWindow::onTargetHit);
    connect(timer, &QTimer::timeout, this, &GameWindow::onTimerEmit);

    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    timer->start();
}

void GameWindow::closeEvent (QCloseEvent *event){
    player->pause();
    timer->stop();
    gameStatus = stop;
    parentWidget()->show();
}
GameWindow* GameWindow::restartGame() {
    this->close();
    return new GameWindow(parentWidget(), gameSettings, drawVec);
}
void GameWindow::paintEvent(QPaintEvent *event) {
    if (curDrawVec) {
        QPainter painter(this);

       drawOneVec(&painter, Qt::red, targetWidget->getTargetPhysics()->getVel());
       drawOneVec(&painter, QColor::fromRgb(255,0,255), targetWidget->getTargetPhysics()->getF());
       drawOneVec(&painter, QColor::fromRgb(255,102,178, 100), targetWidget->getTargetPhysics()->getFs());
       drawOneVec(&painter, QColor::fromRgb(0,255,255, 100), targetWidget->getTargetPhysics()->getFm());
       drawOneVec(&painter, QColor::fromRgb(102,0,102, 100), targetWidget->getTargetPhysics()->getFo());
       drawOneVec(&painter, Qt::blue, targetWidget->getTargetPhysics()->getAccel());

    }

}

void GameWindow::drawOneVec(QPainter* painter, QColor color, Vec2D v) {
    painter->setPen(QPen(color, 2));
    painter->drawLine(targetWidget->getPos().toQPoint(), (targetWidget->getPos() + v).toQPoint());
}
bool GameWindow::isInWindow() {
    auto p = targetWidget->getPos();
    return ((0 < (p.x - gameSettings.borderPadding.x) && (p.x + gameSettings.borderPadding.x) < size().width()) && (0 < (p.y - gameSettings.borderPadding.y) && (p.y + gameSettings.borderPadding.y) < size().height()));
}
void GameWindow::onTargetHit() {
    if (gameStatus == playing) {
        targetWidget->getTargetProps()->hit(gameSettings.hitStrength);
        if (!targetWidget->getTargetProps()->isAlive()) {
            gameStatus = win;
            startDeathProcess();
        } else {
            player->setSource(QUrl(gameSettings.damageSound()));
            player->play();
        }
        targetWidget->getTargetImage()->setPixmap(QPixmap(targetWidget->getTargetProps()->getImage()).scaled(targetWidget->getTargetProps()->picSize.toQSize()));
        qDebug() << "HIT! HP left: " << targetWidget->getTargetProps()->hp;
    }


}

void GameWindow::startDeathProcess(){
    curDrawVec = false;
    repaint();
    timer->stop();
    kataf->show();

    player->setSource(QUrl(gameSettings.endSong()));
    player->play();
    QPropertyAnimation* animation = new QPropertyAnimation(kataf, "pos");
    animation->setDuration(8000);
    animation->setStartValue(QPoint(-kataf->size().width(),-kataf->size().height()));
    animation->setEndValue((targetWidget->getPos() - targetWidget->getTargetProps()->picSize).toQPoint());

    connect(animation, &QPropertyAnimation::finished, this, [this]() {
        qDebug() << "PICKED UP";
        targetWidget->hide();
        QPropertyAnimation* animation = new QPropertyAnimation(kataf, "pos");

        animation->setDuration(6000);
        animation->setStartValue((targetWidget->getPos() - targetWidget->getTargetProps()->picSize).toQPoint());
        animation->setEndValue(QPoint(this->size().width(), this->size().height()));

        animation->start();

        connect(animation, &QPropertyAnimation::finished, this, [this]() {
            qDebug() << "FINISHED GAME";
            WinDialog * wd = new WinDialog(this);
            connect(wd, &WinDialog::restart, this, [this, wd](){
                wd->close();
                restartGame()->show();
            });

            connect(wd, &WinDialog::goMenu, this, [this, wd](){
                wd->close();
                this->close();
                if (this->parentWidget() != nullptr)
                    this->parentWidget()->show();
            });
            wd->show();
            kataf->hide();
        });



    });

    animation->start(); // start the animation
}
void GameWindow::onTimerEmit() {

    if (targetWidget->isTriggered(cursorPos)) {
        double k = targetWidget->getTriggerRadius() / (cursorPos.distance(targetWidget->getPos())+1);
        Vec2D F = (cursorPos - (targetWidget->getPos() - k*(targetWidget->getPos() - cursorPos))) ;
        targetWidget->getTargetPhysics()->changeFm(F*200*gameSettings.movementSettings.mouseFactor);
    } else {

            if (targetWidget->getTargetPhysics()->getVel().scal() < 2 && isInWindow()) {
                        qDebug() << "Stop timer!";
                        targetWidget->getTargetPhysics()->changeVel(Vec2D());
                        timer->stop();
                    }
            targetWidget->getTargetPhysics()->changeFm(Vec2D());
    }

    if (!isInWindow()) {
        auto dopF = ((Vec2D::fromSize(size()) / 2) - targetWidget->getPos()) * 160 * gameSettings.movementSettings.borderFactor;
        targetWidget->getTargetPhysics()->changeFo(dopF);
    } else {
        targetWidget->getTargetPhysics()->changeFo(Vec2D());
    }
    targetWidget->updatePos(((double)timer->interval()) / 1000);
    repaint();


}
void GameWindow::mouseMoveEvent(QMouseEvent* event) {
    prevCursorPos = cursorPos;
    cursorPos = Vec2D{event->pos().x(), event->pos().y()};

    mouseMoveVec = cursorPos - prevCursorPos;
    distance = Vec2D{event->pos().x(), event->pos().y()}.distance(targetWidget->getPos());

    if (targetWidget->isTriggered(cursorPos) && gameStatus == playing) {
        if (!timer->isActive())
            timer->start();
    }
}



GameWindow::~GameWindow()
{
    delete ui;
}

