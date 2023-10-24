#include <QTimer>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QLineEdit>
#include <QRandomGenerator>
#include <QRegularExpression>
#include <QTextEdit>
#include <QPropertyAnimation>
#include <QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    int * WTime = new int;
    *WTime = 1;

    int * NowInGame = new int;
    *NowInGame =  QRandomGenerator::global()->bounded(9);

    QList<int> * Winner = new QList<int>;
    for (int i = 1; i <=9; i++)
        Winner->append(i);
    // Путь к папке с изображениями
    QString path = "5gr/";
    // path = "images/";
    // Заполнение каждого QTextEdit изображением
    QTextEdit* textEdits[] = { ui->textEdit_1, ui->textEdit_2, ui->textEdit_3,
                                ui->textEdit_4, ui->textEdit_5, ui->textEdit_6,
                                ui->textEdit_7, ui->textEdit_8, ui->textEdit_9 };

    for (int i = 0; i < 9; i++) {
        // Установка содержимого и политики размера QTextEdit
        textEdits[i]->setHtml("<img src='" + path + QString::number(i + 1) + ".jpg' width='131' height='151'>");
        textEdits[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    // Считывание считалочек из файла
    QString filePath = "schit.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    QStringList schitalki;
    while (!in.atEnd()) {
        schitalki << in.readLine().trimmed();
    }

    file.close();

    QString schitalka;
    if (!schitalki.isEmpty()) {
        schitalka = schitalki.at(QRandomGenerator::global()->bounded(schitalki.size()));
    } else {
        return;
    }

    // Разбиение считалочки на слова
    QStringList words = schitalka.split(QRegularExpression("[^\\p{L}\\d]+"), Qt::SkipEmptyParts);
    int wordCount = words.size();

    // Инициализация таймера
    QTimer *timer = new QTimer(this);
    bool isFirstRound = true;


    connect(timer, &QTimer::timeout, [this, words, wordCount, timer, WTime, NowInGame, Winner](){
             if (Winner->length() == 1) {
                 timer->stop();

                 QLineEdit* lastLineEdit = findChild<QLineEdit*>("lineEdit_" + QString::number(Winner->first()));
                 if (lastLineEdit) {
                     lastLineEdit->setAlignment(Qt::AlignCenter);
                     int x = lastLineEdit->x();
                     int y = lastLineEdit->y();
                     QPropertyAnimation *animation = new QPropertyAnimation(lastLineEdit, "geometry");
                     animation->setDuration(3000);
                     animation->setStartValue(QRect(x, y, lastLineEdit->width(), lastLineEdit->height()));
                     animation->setEndValue(QRect((width()-lastLineEdit->width())/2, (height()-lastLineEdit->height())/2 + 100, lastLineEdit->width(), lastLineEdit->height()));
                     animation->setEasingCurve(QEasingCurve::OutBounce);
                     animation->start();
                      lastLineEdit->setText("Поздравляем!");
                 }
                 QTextEdit* lastTextEdit = findChild<QTextEdit*>("textEdit_" + QString::number(Winner->at(*NowInGame)));
                 if (lastTextEdit) {
                     lastTextEdit->setAlignment(Qt::AlignCenter);
                     int x = lastTextEdit->x();
                     int y = lastTextEdit->y();
                     QPropertyAnimation *animation = new QPropertyAnimation(lastTextEdit, "geometry");
                     animation->setDuration(3000);
                     animation->setStartValue(QRect(x, y, lastTextEdit->width(), lastTextEdit->height()));
                     animation->setEndValue(QRect((width()-lastTextEdit->width())/2, (height()-lastTextEdit->height())/2, lastTextEdit->width(), lastTextEdit->height()));
                     animation->setEasingCurve(QEasingCurve::OutBounce);
                     animation->start();

                     QTimer *timer = new QTimer(this);


                     timer->setInterval(3000);

                     connect(timer, &QTimer::timeout, this, [=]() {

                         QLabel *imageLabel = new QLabel(this);
                         imageLabel->setPixmap(QPixmap("5gr/11.png"));
                         imageLabel->setGeometry(
                             (width() - imageLabel->pixmap().width()) / 2,
                             (height() - imageLabel->pixmap().height()) / 2 - 50,
                             imageLabel->pixmap().width(),
                             imageLabel->pixmap().height()
                         );
                         imageLabel->show();

                     });

                     QMediaPlayer * player = new QMediaPlayer();
                     QAudioOutput * audioOutput = new QAudioOutput;
                     audioOutput->setVolume(100);
                     player->setAudioOutput(audioOutput);
                     player->setSource(QUrl("5gr/konec.mp3"));
                     player->play();

                     timer->start();

                 }

                 return;
             }
        *NowInGame = *NowInGame % Winner->length();

        for (int ind : *Winner) {
            QLineEdit* le = findChild<QLineEdit*>("lineEdit_" + QString::number(ind));
            if(le) {
                le->clear();
            }
            QTextEdit* lte = findChild<QTextEdit*>("textEdit_" + QString::number(ind));
            if(lte) {
                lte->setStyleSheet("");
            }
        }


        QLineEdit* le = findChild<QLineEdit*>("lineEdit_" + QString::number(Winner->at(*NowInGame)));
        if(le) {
            le->clear();
        }
        QTextEdit* lte = findChild<QTextEdit*>("textEdit_" + QString::number(Winner->at(*NowInGame)));
        if(lte) {
            lte->setStyleSheet("");
        }

        le->setText(words[*WTime - 1]);
        QTextEdit* currentTextEdit = findChild<QTextEdit*>("textEdit_" + QString::number(Winner->at(*NowInGame)));
        if(currentTextEdit) {
            currentTextEdit->setStyleSheet("border: 2px solid yellow;");
        }

        if (*WTime  == words.length()) {
            timer->stop();
            *WTime = 1;
            QTimer::singleShot(5200, [this, NowInGame, Winner, timer, WTime]() {
                QLineEdit* lastLineEdit = findChild<QLineEdit*>("lineEdit_" + QString::number(Winner->at(*NowInGame)));
                if(lastLineEdit) {
                    delete lastLineEdit;
                }
                Winner->removeAt(*NowInGame);
                timer->start();
            });

            QTextEdit* lastTextEdit = findChild<QTextEdit*>("textEdit_" + QString::number(Winner->at(*NowInGame)));
            if(lastTextEdit) {

                QMediaPlayer * player = new QMediaPlayer();
                QAudioOutput * audioOutput = new QAudioOutput;
                audioOutput->setVolume(100);
                player->setAudioOutput(audioOutput);
                player->setSource(QUrl("5gr/udal.mp3"));
                player->play();

                QPropertyAnimation *animation = new QPropertyAnimation(lastTextEdit, "geometry");
                animation->setDuration(5000);
                QRect endValue = lastTextEdit->geometry();
                endValue.setWidth(0);
                endValue.setHeight(0);
                animation->setEndValue(endValue);
                connect(animation, &QPropertyAnimation::finished, lastTextEdit, &QWidget::deleteLater);
                animation->start(QAbstractAnimation::DeleteWhenStopped);
            }

        } else {
            *WTime = *WTime + 1;
            *NowInGame = *NowInGame + 1;
        }




    });

    timer->setInterval(1000);
    timer->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}


