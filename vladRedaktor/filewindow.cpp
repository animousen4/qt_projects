#include "filewindow.h"
#include "ui_filewindow.h"

#include <QDebug>
#include <QString>
#include <QFile>
#include <QDataStream>
#include <string>

using namespace std;

bool DIVIDOR(QChar c) {
    return (c == ' ' || c == ',' || c == '.' || c == ':' || c == ')' || c == '(' || c == '\t'
        || c == ';' || c == '\n' || c == '\"' || c == '!' || c == '?' || c == '-');
}

QString Simvol (QChar c){
    if (c == ' ') return "[пробел]";
    else if (c == '\n') return "[enter]";
    else return QString(c);
}

struct Count{
    QChar s;
    unsigned short num;
    Count* next;
};

struct Pares {
    QChar s1;
    QChar s2;
    unsigned short num;
    Pares* next;
};

filewindow::filewindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::filewindow)
{
    ui->setupUi(this);
}

filewindow::~filewindow()
{
    delete ui;
}

void filewindow::on_pushButton_clicked()
{
    QString FileName = ui->FileName->text();
    QFile fin(FileName);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
    QTextStream in(&fin);
    QString Text = in.readAll();

    ui->fileout->append("Введенный текст:");
    ui->fileout->append(Text + "\n");

    unsigned short i, j, zu, num, k, tmp; bool inWord, addpare, addsym, zamena; QChar temp;
    Pares Spis[256]; Count Symb[256];
        inWord = false;
        k = 0;
        i = 0;
        zu = 0;
        num = 0;
        Text = Text + " ";
        while (i!= Text.length() - 1) {

            j = 0;
            addsym = false;
            while (j != num && !addsym){
                if (Text[i] == Symb[j].s){
                    Symb[j].num = Symb[j].num + 1;
                    addsym = true;
                }
                else j = j + 1;
            }
            if (!addsym){
            Symb[j].s = Text[i];
            Symb[j].num = 1;
            num = num + 1;
            }

            j = 0;
            addpare = false;
            while (j != zu && !addpare)
            {
                if (Text[i] == Spis[j].s1 && Text[i+1] == Spis[j].s2) {
                    Spis[j].num = Spis[j].num + 1;
                    addpare = true;
                }
                else j = j + 1;
            }
            if (!addpare) {
            Spis[j].s1 = Text[i];
            Spis[j].s2 = Text[i+1];
            Spis[j].num = 1;
            zu = zu + 1;
            }

            if (DIVIDOR(Text[i]))
                        inWord = false;
                    else
                        if (inWord == false) {
                            inWord = true;
                            k = k + 1;
                        }
            i = i + 1;
        }
        QString str = "Количество слов в тексте: " + QString::number(k) + ".\n";
        ui->fileout->append(str);

        zamena = true;
        j = 0;
        while (zamena || j < num - 1) {
                i = 0;
                zamena = false;
                while (i < num - j - 1) {
                    if (Symb[i].num < Symb[i + 1].num) {
                        temp = Symb[i].s; tmp = Symb[i].num;
                        Symb[i].s = Symb[i + 1].s; Symb[i].num = Symb[i + 1].num;
                        Symb[i + 1].s = temp; Symb[i + 1].num = tmp;
                        zamena = true;
                    }
                    i = i + 1;
                }
                j = j + 1;
            }

        i = 0;
            while (i != num) {
                QString str = "Символ " + Simvol(Symb[i].s) + " встречается " + QString::number(Symb[i].num) + " раз(а).";
                ui->fileout->append(str);
                i = i + 1;
            }

        ui->fileout->append("");
        i = 0;
            while (i != zu - 1) {
                QString str = "Пара символов " + Simvol(Spis[i].s1) + " и " + Simvol(Spis[i].s2) + " встречается " + QString::number(Spis[i].num) + " раз(а).";
                ui->fileout->append(str);
                i = i + 1;
            }
}

