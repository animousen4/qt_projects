#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QString>
#include <QChar>
#include <QRegularExpression>
#include <QTime>
#include <QMediaPlayer>
#include <QAudioOutput>

using namespace std;

void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

struct List {
    QString info;
    List *next;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->venok->hide();
    ui->pobeda->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    srand(time(0));
    ui->pushButton->hide();
    QFile fin("input.txt");
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) return;
        QString Names  = fin.readAll();
        List* head; List* temp; List* curr; unsigned short chislo; unsigned short count, i, j; unsigned short pos;
        QRegularExpression rx("(\\ |\\,|\\.|\\:|\\t|\\n|\\?|\\-|\\!)");
        QStringList Name = Names.split(rx);
        head = new List;
        head->info = Name[0];
        head->next = head;
        curr = head;
        temp = new List;
        i = 1;
        while (i!= 9) {
            temp = new List;
            temp->info = Name[i];
            curr->next = temp;
            curr = temp;
            i = i + 1;
        }
        curr->next = head;
        pos = rand() % 9 + 1;
        curr = head;
        count = 1;
        while (count != pos) {
            temp = curr;
            curr = curr->next;
            count = count + 1;
        }
        chislo = rand() % 8 + 1;

        QFile sch("schitalochki.txt");
        if (!sch.open(QIODevice::ReadOnly | QIODevice::Text)) return;
        QString Schitalochki;
        Schitalochki = sch.readAll();
        QString Schitalochka = " ";
        i = 0;
        while ((int)Schitalochki[i].unicode() != chislo + 48)
        {
            i = i + 1;
        }
        j = 0;
        while ((int)Schitalochki[i].unicode() != chislo + 49 && i!=Schitalochki.length()-1) {
            Schitalochka = Schitalochka + Schitalochki[i];
            i = i + 1;
            j = j + 1;
        }
        Schitalochka[1] = ' ';
        QStringList Word;
        Word = Schitalochka.split(rx);
        Word.removeAll("");
        chislo = Word.length() - 1;
        count = 0;
        i = 0;
        while (temp->next != temp) {
            if (count == chislo) {
                if (curr->info == "Гнилозуб") {
                    ui->GK ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: red; "
                                                 "}");
                    ui->Gnilozub->setText(Word[i]);
                    delay();
                    ui->Gnilozub->hide();
                    ui->GK->hide();
                }
                else if (curr->info == "Зайцев") {
                    ui->ZD ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: red; "
                                                 "}");
                    ui->Zaicev->setText(Word[i]);
                    delay();
                    ui->Zaicev->hide();
                    ui->ZD->hide();
                }
                else if (curr->info == "Козыро") {
                    ui->KI ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: red; "
                                                 "}");
                    ui->Koziro->setText(Word[i]);
                    delay();
                    ui->Koziro->hide();
                    ui->KI->hide();
                }
                else if (curr->info == "Лужкова") {
                    ui->LU ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: red; "
                                                 "}");
                    ui->Luzhkova->setText(Word[i]);
                    delay();
                    ui->Luzhkova->hide();
                    ui->LU->hide();
                }
                else if (curr->info == "Медведев") {
                    ui->MI ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: red; "
                                                 "}");
                    ui->Medvedev->setText(Word[i]);
                    delay();
                    ui->Medvedev->hide();
                    ui->MI->hide();
                }
                else if (curr->info == "Фельдшеров") {
                    ui->FP ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: red; "
                                                 "}");
                    ui->Feldsherov->setText(Word[i]);
                    delay();
                    ui->Feldsherov->hide();
                    ui->FP->hide();
                }
                else if (curr->info == "Фролова") {
                    ui->FI ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: red; "
                                                 "}");
                    ui->Frolova->setText(Word[i]);
                    delay();
                    ui->Frolova->hide();
                    ui->FI->hide();
                }
                else if (curr->info == "Цыбулька") {
                    ui->TV ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: red; "
                                                 "}");
                    ui->Tsybulka->setText(Word[i]);
                    delay();
                    ui->Tsybulka->hide();
                    ui->TV->hide();
                }
                else if (curr->info == "Яцукевич") {
                    ui->YE ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: red; "
                                                 "}");
                    ui->Yatsukevich->setText(Word[i]);
                    delay();
                    ui->Yatsukevich->hide();
                    ui->YE->hide();
                }
                player = new QMediaPlayer();
                QAudioOutput * audioOutput = new QAudioOutput;
                audioOutput->setVolume(100);
                player->setAudioOutput(audioOutput);
                player->setSource(QUrl("qrc:/music/fail.mp3"));
                player->play();
                temp->next = curr->next;
                delete(curr);
                curr = temp->next;
                count = 0;
                i = 0;
            }
            else {
                if (curr->info == "Гнилозуб") {
                    ui->Gnilozub->setText(Word[i]);
                    ui->GK ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: red; "
                                                 "}");
                    delay();
                    ui->GK ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: white; "
                                                 "}");
                }
                else if (curr->info == "Зайцев") {
                    ui->Zaicev->setText(Word[i]);
                    ui->ZD ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: red; "
                                                 "}");
                    delay();
                    ui->ZD ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: white; "
                                                 "}");
                }
                else if (curr->info == "Козыро") {
                    ui->Koziro->setText(Word[i]);
                    ui->KI ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: red; "
                                                 "}");
                    delay();
                    ui->KI ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: white; "
                                                 "}");
                }
                else if (curr->info == "Лужкова") {
                    ui->Luzhkova->setText(Word[i]);
                    ui->LU ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: red; "
                                                 "}");
                    delay();
                    ui->LU ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: white; "
                                                 "}");
                }
                else if (curr->info == "Медведев") {
                    ui->Medvedev->setText(Word[i]);
                    ui->MI ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: red; "
                                                 "}");
                    delay();
                    ui->MI ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: white; "
                                                 "}");
                }
                else if (curr->info == "Фельдшеров") {
                    ui->Feldsherov->setText(Word[i]);
                    ui->FP ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: red; "
                                                 "}");
                    delay();
                    ui->FP ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: white; "
                                                 "}");
                }
                else if (curr->info == "Фролова") {
                    ui->Frolova->setText(Word[i]);
                    ui->FI ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: red; "
                                                 "}");
                    delay();
                    ui->FI ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: white; "
                                                 "}");
                }
                else if (curr->info == "Цыбулька") {
                    ui->Tsybulka->setText(Word[i]);
                    ui->TV ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: red; "
                                                 "}");
                    delay();
                    ui->TV ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: white; "
                                                 "}");
                }
                else if (curr->info == "Яцукевич") {
                    ui->Yatsukevich->setText(Word[i]);
                    ui->YE ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: red; "
                                                 "}");
                    delay();
                    ui->YE ->setStyleSheet("QLabel {"
                                                 "border-style: solid;"
                                                 "border-width: 3px;"
                                                 "border-color: white; "
                                                 "}");
                }
                count = count + 1;
                curr = curr->next;
                temp = temp->next;
                i = i + 1;
            }
        }
            if (curr->info == "Гнилозуб") {
                ui->GK->move(380,220);
                ui->Gnilozub->hide();
            }
            else if (curr->info == "Зайцев") {
                ui->ZD->move(380,220);
                ui->Gnilozub->hide();
            }
            else if (curr->info == "Козыро") {
                ui->KI->move(380,220);
                ui->Koziro->hide();
            }
            else if (curr->info == "Лужкова") {
                ui->LU->move(380,220);
                ui->Luzhkova->hide();
            }
            else if (curr->info == "Медведев") {
                ui->MI->move(380,220);
                ui->Medvedev->hide();
            }
            else if (curr->info == "Фельдшеров") {
                ui->FP->move(380,220);
                ui->Feldsherov->hide();
            }
            else if (curr->info == "Фролова") {
                ui->FI->move(380,220);
                ui->Frolova->hide();
            }
            else if (curr->info == "Цыбулька") {
                ui->TV->move(380,220);
                ui->Tsybulka->hide();
            }
            else if (curr->info == "Яцукевич") {
                ui->YE->move(380,220);
                ui->Yatsukevich->hide();
            }
        delay();
        player = new QMediaPlayer();
        QAudioOutput * audioOutput = new QAudioOutput;
        audioOutput->setVolume(100);
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl("qrc:/music/win.mp3"));
        player->play();
        ui->venok->show();
        ui->pobeda->show();
}

