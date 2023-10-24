#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MyLayout.h"
#include "PlayerWidget.h"
#include <QVBoxLayout>
#include "circularlayout.h"
#include "dialogfile.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <regex>
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer;
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &MainWindow::timeIsUp);

    connect(ui->action_open_file, &QAction::triggered, this, &MainWindow::open_file);
    MyLayout* layout = new MyLayout(nullptr, 350);
    main_layout = layout;

    this->ui->centralwidget->setStyleSheet("background-color: yellow");

    QVector <QString> files = {"images/luzhkova.jpg", "images/medvedev.jpg", "images/kozyro.jpg", "images/cybulka.jpg", "images/zaycev.jpg", "images/feldsherov.jpg", "images/frolova.jpg", "images/karskiy.jpg"};

    for (int i = 0; i < 8; i++){
        Player* pl = new Player(files[i]);
        layout->addWidget(pl);
    }

    this->ui->centralwidget->setLayout(layout);
}

void MainWindow::timeIsUp() {

    timer->stop();
    qDebug() << "timer is up";

    if (main_layout->players.size() == 1) {
        timer->stop();
        //какие-то деяния при победе

        qDebug() << "the winner is found";

        return;
    }
    index_player %= main_layout->players.size(); // всегда на всякий сбрасываем лишнее, сделав тем самым круг

    // Что бы не случилось, сначала обрисовываем текущего игрока
    Player* cur = dynamic_cast <Player*> (main_layout->itemAt(index_player)->widget());

    cur->word->setText(cur_words[cur_cnt_words]);
    cur->word->setStyleSheet("border: 2px solid red");
    Player* prev;
    if (index_player > 0) {
        // [*] (*) * * *
        prev = dynamic_cast <Player*> (main_layout->itemAt(index_player - 1)->widget());

    } else {
        // (*) * * * [*]
        prev = dynamic_cast <Player*> (main_layout->players.last()->widget());
    }

    prev->word->setText("");
    prev->word->setStyleSheet("");



    // Если суждено помереть...
    if (cur_cnt_words == cur_words.size() - 1) {
        QTimer* tempTimer = new QTimer();
        tempTimer->setSingleShot(true);
        tempTimer->setInterval(1000);
        // Нужно подождать, чтобы убитый повисел еще немного
        connect(tempTimer, &QTimer::timeout, this, [this]() {
            qDebug() << "Killing " << index_player;
            main_layout->players.at(index_player)->widget()->deleteLater();
            cur_cnt_words = 0;
            this->timer->start();
        });

        // Запускаем экзекуцию с задержкой в 1 сек
        tempTimer->start();

        // Если игрок помер, то смысла увеличивать индексы на единичку нет, потому что на место померевшего станет следующий, с которого нужно будет начать счет дальше
        // Поэтому ставим else
    } else {
        index_player++;
        cur_cnt_words++;
        this->timer->start();
    }

//    qDebug() << "cur player index is " << index_player << "\n" << "cnt players " <<  main_layout->players.size();
//    qDebug() << "cur cnt words " << cur_cnt_words;

//    int prev_index;

//    if (index_player) prev_index = index_player - 1;
//    else prev_index = main_layout->players.size() - 1;

//    qDebug() << "prev is " << prev_index;

//    Player* prev = dynamic_cast <Player*> (main_layout->itemAt(prev_index)->widget());

//    if (cur_cnt_words - 1 == -1) {

//        if (!game_just_started){

//            main_layout->players.at(index_player)->widget()->deleteLater();
//            qDebug() << "player " << index_player << " deleted";

////            if (index_player) index_player--;
////            else index_player = main_layout->players.size() - 1;
//            qDebug() << "index_player reduced now it's " << index_player;

//        }
//        else game_just_started = false;

//    }
//    else {
//        prev->word->setStyleSheet("border: none");
//        prev->word->setText("");
//    }

//    Player* cur = dynamic_cast <Player*> (main_layout->itemAt(index_player)->widget());

//    cur->word->setText(cur_words[cur_cnt_words]);
//    cur->word->setStyleSheet("border: 2px solid red");




}

int MainWindow::random(int low, int high)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

void MainWindow::open_file() {

    if (MainWindow::is_game_on) return;

    DialogFile* miniWindow = new DialogFile;
    MainWindow::dialog = miniWindow;
    connect(miniWindow->nameEnteredBtn, &QPushButton::pressed, this, &MainWindow::extractName);
    miniWindow->show();
}

void MainWindow::extractName() {
    QString fileName = MainWindow::dialog->fileNameEdit->text();

    ifstream fin(fileName.toStdString());

    if(!fin.is_open()){
        QMessageBox msgBox;
        msgBox.setText("there is no such file");
        msgBox.exec();
        return;
    }

    string s;

    vector <string> rhymes;

    while (getline(fin, s)) {
        rhymes.push_back(s);
    }

    int n = random(0, rhymes.size() - 1);

    qDebug() << n;

    string processed_s = rhymes[n];

    QRegularExpression rx("(\\ |\\,|\\.|\\:|\\t|\\n|\\?|\\-|\\!)");
    QStringList exploded = QString::fromStdString(processed_s).split(rx);

    /*for (int i = 0; i < int(exploded.size()); i++){
        qDebug() << exploded[i] << endl;
    }*/

    MainWindow::cur_words = exploded;

    MainWindow::dialog->close();
    fin.close();

    MainWindow::startGame();
}

void MainWindow::startGame() {

    qDebug() << "game started";

    int n = main_layout->players.size();

    index_player = random(0, n - 1);
    cur_cnt_words = 0;

    game_just_started = true;

    timer->start();

    qDebug() << "timer started";
};

MainWindow::~MainWindow()
{
    delete ui;
}

