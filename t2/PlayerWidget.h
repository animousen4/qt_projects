#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>

class Player : public QWidget
{
    Q_OBJECT
public:

    Player(QString fileName) {
        QPixmap pm(fileName);
        image->setScaledContents(true);
        image->setPixmap(pm.scaled(QSize(150, 150), Qt::KeepAspectRatio));
        image->resize(150, 150);

        image->setStyleSheet("border: 2px solid green");
        QLayout* playerLayout = new QVBoxLayout(this);
        playerLayout->addWidget(image);


        //word->setText("curWord");
        QFont font;
        font.setPixelSize(15);
        font.setWeight(QFont::Bold);

        word->setFont(font);
        word->setAlignment(Qt::AlignHCenter);
        //word->setStyleSheet("border: 0px");
        playerLayout->addWidget(word);

        this->setLayout(playerLayout);
    };
    ~Player() {};

    bool is_alive = true;
    //bool is_active = false;
    QLabel* word = new QLabel(this);
    QLabel* image = new QLabel(this);

public slots:
    /*void playerActivated() {
        if (!if_first_chosen) {

        }
    }*/

private:

};

#endif // PLAYERWIDGET_H
