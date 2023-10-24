#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <TableModels.h>
#include <QLabel>
#include <prettybloc.h>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setMinimumWidth(1200);

    ui->table1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->mergeTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->verticalLayout->setAlignment(Qt::AlignTop);

    connect(ui->loadBagButton, &QPushButton::clicked, this, [this](){
        s1 = new Bag();
        s2 = new Bag();
        m = new Bag();

        loadData();
        updateData();

    });

    connect(ui->loadFruitsButton, &QPushButton::clicked, this, [this](){
        s1 = new Fruit();
        s2 = new Fruit();
        m = new Fruit();

        loadData();
        updateData();

    });

    connect(ui->loadBagBinButton, &QPushButton::clicked, this, [this](){
        s1 = new Bag();
        s2 = new Bag();
        m = new Bag();

        loadData(true);
        updateData();

    });

    connect(ui->loadFruitsBinButton, &QPushButton::clicked, this, [this](){
        s1 = new Fruit();
        s2 = new Fruit();
        m = new Fruit();

        loadData(true);
        updateData();

    });

    connect(ui->sortButton, &QPushButton::clicked, this, [this](){
        s1->Sort();
        s2->Sort();
        m->Sort();

        updateData();

    });

    connect(ui->mergeButton, &QPushButton::clicked, this, [this](){
        m->merge(s1, s2);
        updateData();
    });

    connect(ui->toFileButton, &QPushButton::clicked, this, [this](){
        QFile outputFile("output.txt");
        m->toText(outputFile);
    });

    connect(ui->toBinFileButton, &QPushButton::clicked, this, [this](){
        QFile outputFile("output.bin.txt");
        m->toBin(outputFile);
    });
    connect(ui->searchButton, &QPushButton::clicked, this, [this](){
        QString data = m->findData(ui->searchLineEdit->text());

        QMessageBox * messageBox = new QMessageBox(this);
        messageBox->setText(data);
        messageBox->show();
    });

}

void MainWindow::loadData(bool bin){
    QFile file(ui->fileEdit1->text());
    if (bin)
        s1->fromBin(file);
    else
        s1->fromText(file);

    QFile file2(ui->fileEdit2->text());

    if (bin)
        s2->fromBin(file2);
    else
        s2->fromText(file2);
}


void MainWindow::updateData() {

        PrettyTableModel * model1 = new PrettyTableModel(this, s1->getItems());
        ui->table1->setModel(model1);

        PrettyTableModel * model2 = new PrettyTableModel(this, s2->getItems());
        ui->table2->setModel(model2);

        PrettyTableModel * model3 = new PrettyTableModel(this, m->getItems());
        ui->mergeTable->setModel(model3);

}





MainWindow::~MainWindow()
{
    delete ui;
}

