#ifndef COUNTINGMANAGER_H
#define COUNTINGMANAGER_H

#include <QString>
#include <QChar>
#include <QVector>
#include <QRegularExpression>
class CountingManager {
    public:
        QString str;
        QVector<QChar> delimiter;

        CountingManager(QString _str = "",QVector<QChar> _delimiter = { ' ', '.',',', '!', '?',';',':', '-', '\\', '|', '/' , '\n'}) : str(_str), delimiter(_delimiter) {

        }
        QVector<QString> getWords() {
                QVector<QString> words;

                words = str.split(QRegularExpression("[\\s.,:;!?]+"));
                return words;
            }
};
#endif // COUNTINGMANAGER_H
