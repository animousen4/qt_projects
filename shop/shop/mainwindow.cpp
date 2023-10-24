#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableView>
#include <QMessageBox>
#include "abstractclass.h"
#include "fruit.h"
#include <QVector>
#include <QString>
#include "qtableviewmodel.h"
#include "bag.h"

#include <algorithm>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->firstSet_tbl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->secondSet_tbl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->mergedSet_tbl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->firstBag_tbl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->secondBag_tbl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->mergedBags_tbl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->openFiles_btn, &QPushButton::pressed, this, &MainWindow::openFiles);
    connect(ui->sortSets_btn, &QPushButton::pressed, this, &MainWindow::sortSets);
    connect(ui->mergeSets_btn, &QPushButton::pressed, this, &MainWindow::mergeSets);
    connect(ui->findObject_btn, &QPushButton::pressed, this, &MainWindow::findSmth);

    connect(ui->sortBags_btn, &QPushButton::pressed, this, &MainWindow::sortBags);
    connect(ui->mergeBags_btn, &QPushButton::pressed, this, &MainWindow::mergeBags);
    //connect(ui->findObject_btn, &QPushButton::pressed, this, &MainWindow::findSmth);



    a1 = new Fruit();
    a2 = new Fruit();
    a3 = new Fruit();

    b1 = new Bag();
    b2 = new Bag();
    b3 = new Bag();
}

void MainWindow::mergeBags() {
    b3->merge(b1, b2);
    updateTables();

    bool isOk = b3->putData(ui->mergedBags_edit->text());
    if (!isOk) {
        QMessageBox::warning(this, "Attention", "Could not find " + ui->mergedBags_edit->text());
    }
}

void MainWindow::mergeSets() {
    a3->merge(a1, a2);
    updateTables();

    bool isOk = a3->putData(ui->mergedProd_edit->text());
    if (!isOk) {
        QMessageBox::warning(this, "Attention", "Could not find " + ui->mergedProd_edit->text());
    }
}

void MainWindow::findSmth() {

    QString object = ui->findObject_edit->text();

    if (object == "") {
        QMessageBox::warning(this, "Attention", "You didn't enter the name of the object");
    }
    else {
        s2 info1 = a1->findObject(object);
        s2 info2 = a2->findObject(object);

        FindInfo* resultWindow = new FindInfo();
        resultWindow->showInfo(info1, info2);
        resultWindow->show(); 
    }

    return;
}

void MainWindow::sortSets() {
    a1->sortItems();
    a2->sortItems();
    updateTables();
}

void MainWindow::sortBags() {
    b1->sortItems();
    b2->sortItems();
    updateTables();
}

void MainWindow::updateTables() {
    FruitTableModel * model1 = new FruitTableModel(this, a1->getItems(), 0);
    ui->firstSet_tbl->setModel(model1);

    FruitTableModel * model2 = new FruitTableModel(this, a2->getItems(), 0);
    ui->secondSet_tbl->setModel(model2);

    FruitTableModel * model3 = new FruitTableModel(this, a3->getItems(), 0);
    ui->mergedSet_tbl->setModel(model3);


    FruitTableModel* model11 = new FruitTableModel(this, b1->getItems(), 1);
    ui->firstBag_tbl->setModel(model11);

    FruitTableModel* model12 = new FruitTableModel(this, b2->getItems(), 1);
    ui->secondBag_tbl->setModel(model12);

    FruitTableModel* model13 = new FruitTableModel(this, b3->getItems(), 1);
    ui->mergedBags_tbl->setModel(model13);
}

void MainWindow::openFiles() {

    if (ui->prod1_edit->text() == "" || ui->prod2_edit->text() == "" || ui->bag1_edit->text() == ""
        || ui->bag2_edit->text() == "" || ui->mergedProd_edit->text() == "" || ui->mergedBags_edit->text() == "")
    {
        QMessageBox::warning(this, "Attention","You didn't enter all file names");
        return;
    }

    bool isOk = a1->getData(ui->prod1_edit->text());
    if (!isOk) {
        QMessageBox::warning(this, "Attention", "Could not find " + ui->prod1_edit->text());
    }

    isOk = a2->getData(ui->prod2_edit->text());
    if (!isOk) {
        QMessageBox::warning(this, "Attention", "Could not find " + ui->prod2_edit->text());
    }

    isOk = b1->getData(ui->bag1_edit->text());
    if (!isOk) {
        QMessageBox::warning(this, "Attention", "Could not find " + ui->bag1_edit->text());
    }

    isOk = b2->getData(ui->bag2_edit->text());
    if (!isOk) {
        QMessageBox::warning(this, "Attention", "Could not find " + ui->bag2_edit->text());
    }

    updateTables();
}

MainWindow::~MainWindow()
{
    delete ui;
}

