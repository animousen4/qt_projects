#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->verticalLayout_2->setAlignment(Qt::AlignTop);
    connect(ui->loadButton, &QPushButton::clicked, this, [this](){
        QFile file(ui->fileEdit->text());
        stud.fromText(file);
        ui->textEdit->setText(stud.toString());
    });

    connect(ui->sortButton, &QPushButton::clicked, this, [this](){
        stud.sortStud();
        ui->textEdit->setText(stud.toString());
    });
//    s.fromText(file);

//    qDebug() << s.toString();

//    s.sortStud();

//    qDebug() << s.toString();

}

MainWindow::~MainWindow()
{
    delete ui;
}

