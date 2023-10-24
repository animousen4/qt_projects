#include "menudialog.h"
#include "ui_menudialog.h"
#include "gamesettings.h"
#include "gamewindow.h"
#include <QTimer>
MenuDialog::MenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuDialog)
{
    ui->setupUi(this);
    index = 0;
    for (auto t : GameSettings::gameSettings().keys()) {
        ui->difficultyBox->addItem(t);
    }

    this->setFixedSize(size());
    connect(ui->difficultyBox, &QComboBox::currentIndexChanged, this, [this](int index){
        this->index = index;
    });
    connect(ui->exitButton, &QPushButton::clicked, this, [this](){
        close();
    });
    connect(ui->startButton, &QPushButton::clicked, this, [this](){
        GameWindow *gameWindow = new GameWindow(this, GameSettings::gameSettings().values()[index], ui->showVector->checkState());
        gameWindow->show();
        this->hide();

    });
}

MenuDialog::~MenuDialog()
{
    delete ui;
}
