    #include "statcollectordialog.h"
#include "./ui_statcollectordialog.h"
#include <string>
#include <QDebug>
#include <QStringListModel>
using namespace std;

StatCollectorDialog::StatCollectorDialog(QWidget *parent, QTextEdit * textEdit) :
    QDialog(parent),
    ui(new Ui::StatCollectorDialog)
{
    ui->setupUi(this);


    this->textEdit = textEdit;
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(this->textEdit, &QTextEdit::textChanged, this, &StatCollectorDialog::collectStat);
    connect(this->textEdit, &QTextEdit::textChanged, this, &StatCollectorDialog::collectPairStat);
    collectStat();
    collectPairStat();
}
bool StatCollectorDialog::isSeparator(QChar ch) {

    for (auto c: separators) {
        if (c==ch)
            return true;
    }

    return false;
}
void StatCollectorDialog::collectStat() {
        QString symbols = textEdit->toPlainText();
        bool isInWord;
        int wordCounter;
        int i, j;

        isInWord = false;
        wordCounter = 0;

        for (i = 0; i < 65536; i++) {
            symbolAmount[i] = 0;
            sootvSymbols[i] = (QChar)i;
        }

        i = 0;
        j = 0;
        while (i < symbols.length()) {
           symbolAmount[symbols.at(i).unicode()] = symbolAmount[symbols.at(i).unicode()] + 1;
           if (isSeparator(symbols[i])) {
               if (isInWord)
                   wordCounter = wordCounter + 1;
               isInWord = false;
           }
           else
               isInWord = true;
           i = i + 1;
        }
        if (isInWord)
           wordCounter = wordCounter + 1;


        QList<KV> upgradedStat;
        for (int i = 0; i < 65536; i++)
            if (symbolAmount[i])
                upgradedStat.append({sootvSymbols[i], symbolAmount[i]});

        int n = upgradedStat.length();

        for(int i=0; i<n-1; i++) {
                bool swapped = false;
                for(int j=0; j<n-i-1; j++) {
                    if(upgradedStat[j].v < upgradedStat[j+1].v) {
                        swap(upgradedStat[j], upgradedStat[j+1]);
                        swapped = true;
                    }
                }
                if(swapped == false)
                    break;
        }


        QList<QString> s;
        for (i = 0; i < n; i++)
                s.append("Символ '" + displaySymbol(upgradedStat[i].k) + "' встречается " + QString::number(upgradedStat[i].v) + " " + getCase(upgradedStat[i].v));

        QStringListModel *model = new QStringListModel(s, this);
        ui->wordsAmountLabel->setText(QString::number(wordCounter));
        ui->listView->setModel(model);




       //ui->sameCombListView


}

void StatCollectorDialog::collectPairStat() {
    QList<QString> output;
    QMap<QString, int> map;
    QString input = textEdit->toPlainText();

    for (int i = 0; i < input.length() - 1; i++) {
        if (isSeparator(input[i]) || isSeparator(input[i+1]))
            continue;
        QString key = QString(1, input[i].toLower()) + QString(1, input[i+1].toLower());
        QString reversedKey = QString(1, input[i+1].toLower()) + QString(1, input[i].toLower());
        if (key==reversedKey)
            continue;
        if (!map.contains(key)){
            if (!map.contains(reversedKey)) {
                map.insert(key, 1);
            } else {
                int value = map.value(reversedKey);
                map.insert(reversedKey, value+1);
            }
        }else {
            int value = map.value(key);
            map.insert(key, value+1);
        }
    }

    for (auto c : map.asKeyValueRange()) {
        output.append("Пара букв '" + QString(1,c.first[0]) +"' и '" + QString(1,c.first[1]) + "' встречается " + QString::number(c.second) + " " + getCase(c.second));
    }
    QStringListModel *model = new QStringListModel(output, this);
    ui->sameCombListView->setModel(model);
}
QString StatCollectorDialog::getCase(int num) {
    int last = num % 10;
    QString res = "раз";
    if (last > 1 && last < 5)
        res = res + "a";
    return res;

}
QString StatCollectorDialog::displaySymbol(QChar s) {
    if (s.unicode() == 10)
        return "[\\n]";
    if (s.unicode() == 9)
        return "[\\t]";
    if (s.unicode() == 32)
        return "[space]";
    return QString(1, s);
}
StatCollectorDialog::~StatCollectorDialog()
{
    delete ui;
}
