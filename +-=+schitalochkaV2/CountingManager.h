#ifndef COUNTINGMANAGER_H
#define COUNTINGMANAGER_H

#include <QString>
#include <QChar>
#include <QVector>
class CountingManager {
    public:
        QString str;
        QVector<QChar> delimiter;

        CountingManager(QString _str = "",QVector<QChar> _delimiter = { ' ', '.',',', '!', '?',';',':', '-', '\\', '|', '/' , '\n'}) : str(_str), delimiter(_delimiter) {

        }
        QVector<QString> getWords() {
                QVector<QString> words;
                QString currentWord;
                bool delimiterInduck;
                for (QChar strC : str) {
                    delimiterInduck = false;
                    for (QChar delC : delimiter) {
                        if (strC == delC) {
                            if (!currentWord.isEmpty()) {
                                words.push_back(currentWord);
                                currentWord = "";
                            }
                            delimiterInduck = true;
                            break;
                        }
                    }
                    if (!delimiterInduck)
                        currentWord += strC;
                }

                if (!currentWord.isEmpty())
                    words.push_back(currentWord);


                return words;
            }
};
#endif // COUNTINGMANAGER_H
