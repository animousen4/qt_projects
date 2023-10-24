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
        s1 = new MED<Items>();
        s2 = new MED<Price>();
        m = new MED<Med>();
        loadData();
        updateData();

    });

    connect(ui->loadBagBinButton, &QPushButton::clicked, this, [this](){
        s1 = new MED<Items>();
        s2 = new MED<Price>();
        m = new MED<Med>();
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
        m = new MED<Med>(MED<Med>::merge(s1, s2));
        updateData();
    });

    connect(ui->toFileButton, &QPushButton::clicked, this, [this](){
        QFile outputFile("output-merged.txt");
        m->toText(outputFile);

        QFile outputFile1("output-items.txt");
        s1->toText(outputFile1);

        QFile outputFile2("output-price.txt");
        s2->toText(outputFile2);
    });

    connect(ui->toBinFileButton, &QPushButton::clicked, this, [this](){
        QFile outputFile("output-merged.bin");
        m->toBin(outputFile);

        QFile outputFile1("output-items.bin");
        s1->toBin(outputFile1);

        QFile outputFile2("output-price.bin");
        s2->toBin(outputFile2);
    });
    connect(ui->searchButton, &QPushButton::clicked, this, [this](){
        //QString data = m->findData(ui->searchLineEdit->text());
        QString res;
        QVector<Items> itemsBad = s1->findBadMedicine(ui->searchLineEdit->text());
        QVector<Price> itemsBad2 = s2->findBadMedicine(ui->searchLineEdit->text());
        for (auto items : itemsBad){
            res += items.toString() + "\n";
        }
        for (auto price: itemsBad2) {
            res += price.toString() + "\n";
        }
        QMessageBox * messageBox = new QMessageBox(this);
        messageBox->setText(res.isEmpty() ? "Not found" : res);
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

    PrettyTableModel * model1 = new PrettyTableModel(this, s1->getItems(), 0);
    ui->table1->setModel(model1);


    PrettyTableModel * model2 = new PrettyTableModel(this, s2->getItems(), 1);
    ui->table2->setModel(model2);


    PrettyTableModel * model3 = new PrettyTableModel(this, m->getItems(), 2);
    ui->mergeTable->setModel(model3);


}





MainWindow::~MainWindow()
{
    delete ui;
}

