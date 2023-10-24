#ifndef CLIENTINFO_H
#define CLIENTINFO_H
#include <QDateTime>
class ClientInfo {
public:
    QDateTime birthDate;
    QDateTime currentDate;
    int calcDays;

    ClientInfo(QDateTime _birthDate, QDateTime _currentDate, int _calcDays) : birthDate(_birthDate), currentDate(_currentDate), calcDays(_calcDays) {}
};
#endif // CLIENTINFO_H
