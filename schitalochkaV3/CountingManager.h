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

        CountingManager(QString _str = "") : str(_str){

        }
        QVector<QString> getWords() {
                QVector<QString> words;

                words = str.split(QRegularExpression("[\\s.,:;!?，]+"));
                words.removeIf([](QString d){
                    return d.isEmpty();
                });
                return words;
            }
};
#endif // COUNTINGMANAGER_H
