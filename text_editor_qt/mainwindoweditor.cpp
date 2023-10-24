#include "mainwindoweditor.h"
#include "ui_mainwindoweditor.h"
#include <fstream>
#include <QDebug>
#include <QMessageBox>
using namespace std;

MainWindowEditor::MainWindowEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowEditor)
{
    ui->setupUi(this);

    connect(ui->inputThing, &QLineEdit::returnPressed, this, &MainWindowEditor::on_inputThing_returnPressed);
    connect(ui->enterBtn, &QPushButton::pressed, this, &MainWindowEditor::on_inputThing_returnPressed);
    connect(ui->textEdit, &QTextEdit::textChanged, this, &MainWindowEditor::on_textEditor_textChanged);
    connect(ui->textEdit, &QTextEdit::textChanged, this, &MainWindowEditor::assess);


}

MainWindowEditor::~MainWindowEditor()
{
    delete ui;
}

void MainWindowEditor::sortSYmbolsByFrequency(int* freq, QChar* symb, int size) {

    bool changed = true;
    int j = 0;
    int i = 0;

    while (changed) {
      i = 0;
      changed = false;
      while (i + 1 < size) {
          if (freq[i] < freq[i + 1]) {
              swap(freq[i], freq[i + 1]);
              swap(symb[i], symb[i + 1]);
              changed = true;
          }
          i = i + 1;
      }
      j = j + 1;
    }

    return;
}

int MainWindowEditor::countWords(QString s, int* masRep) {
    s += '.';
    int res = 0;
    int i = 0;
    bool isPrevDiv = true;

    while (i < s.length() - 1){

        masRep[s[i].unicode()]++;

        //qDebug() << (QChar(s[i])).unicode();

        if (ifDivider(s[i])){
            if (!isPrevDiv) res++;
            isPrevDiv = true;
        } else isPrevDiv = false;

        i++;
    }

    if (!isPrevDiv) res++;

    return res;
}

void MainWindowEditor::assess(){

    ifstream fin(this->getFile().toStdString(), ios::in);
    string s;

    int cntWords = 0;

    int cntLetters[65536] = {};
    QChar symbols[65536];

    for (int i = 0; i < 65536; i++)
        symbols[i] = (QChar)i;

    while (getline(fin, s)) {
        QString curS = QString::fromStdString(s);
        int dop = countWords(curS, cntLetters);
        cntWords += dop;
    }

    //cntWords = countWords(ui->textEdit->toPlainText(), cntLetters);


    ui->textBrowser->clear();

    QString words = "total amount of words is " + QString::number(cntWords);
    ui->textBrowser->append(words);

    // OPTIMIZATION
    QChar symbolsOptimized[65536];
    int amountOptimized[65536];
    int optSize = 0;

    for (int i = 0; i < 65536; i++) {
        if (cntLetters[i]) {
            symbolsOptimized[optSize] = symbols[i];
            amountOptimized[optSize] = cntLetters[i];
            optSize++;
        }
    }

    this->sortSYmbolsByFrequency(amountOptimized, symbolsOptimized, optSize);

    for (int j = 0; j < 65536; j++) {
        if (cntLetters[j]) {

            //qDebug() << "* " << QChar(symbols[j]).unicode();
            QString dop = "symbol " + QString(symbols[j]) + " appears " + QString::number(cntLetters[j]) + " times";
            ui->textBrowser->append(dop);
        }
    }
}

void MainWindowEditor::on_textEditor_textChanged()
{
    ofstream fout(this->getFile().toStdString(), ios::trunc);

    fout << ui->textEdit->toPlainText().toStdString();
    fout.close();
}



void MainWindowEditor::on_inputThing_returnPressed()
{
    QString fileName = ui->inputThing->text();
    ifstream fin(fileName.toStdString());

    qDebug() << "file name is " << fileName;

    if (fin.is_open()) qDebug() << "opened the file successfully";
    else {
        qDebug() << "couldn't open the file";
        QMessageBox::warning(this, "Attention","File is not found");
    }

    this->setFile(fileName);

    string s;
    while (getline(fin, s)){
        ui->textEdit->append(QString::fromStdString(s));
        //qDebug() << QString::fromStdString(s);
    };

    fin.close();
}
