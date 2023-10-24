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
    timer->setInterval(2000);
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

    qDebug() << "timer is up";

    if (main_layout->players.size() == 1) {
        timer->stop();
        //какие-то деяния при победе

        return;
    }

    Player* prev = nullptr;

    if (index_player) prev = dynamic_cast <Player*> (main_layout->itemAt((index_player - 1) % (main_layout->players.size())));
    else prev = dynamic_cast <Player*> (main_layout->itemAt(main_layout->players.size() - 1));

    qDebug() << index_player << main_layout->players.size();

    for (auto p: main_layout->players) {
        Player * dop = dynamic_cast<Player*>(p->widget());
        qDebug() << dop->word->text();
        //qDebug() << "*" << dop->word << "*" << endl;
    }

    //prev->word->setStyleSheet("border: 2px solid white");
    //prev->word->setText("");

    /*

    Player* cur = dynamic_cast <Player*> (main_layout->itemAt(index_player % (main_layout->players.size())));

    cur->word->setText(cur_words[cur_cnt_words % cur_words.size()]);
    cur->word->setStyleSheet("border: 2px solid red");

    if (cur_cnt_words % (cur_words.size() - 1) == 0){
        main_layout->removeItem(main_layout->itemAt(cur_cnt_words));
        cur_cnt_words = 0;
    }
    else {
        cur->word->setStyleSheet("border: 2px solid white");
        cur->word->setText("");
        index_player++;
    }
    */

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

    timer->start();

    qDebug() << "timer started";
};

MainWindow::~MainWindow()
{
    delete ui;
}

