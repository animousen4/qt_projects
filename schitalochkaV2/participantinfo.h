#ifndef PARTICIPANTINFO_H
#define PARTICIPANTINFO_H
#include <QString>

class ParticipantInfo
{
public:
    ParticipantInfo(QString _studentName, QString _imageFileName);
    ParticipantInfo();
    QString studentName;
    QString imageFileName;

    friend QDataStream &operator>>(QDataStream &in, ParticipantInfo &info) {
        in >> info.imageFileName >> info.studentName;
        return in;
    }
    friend QDataStream &operator<<(QDataStream &out, const ParticipantInfo &info) {
        out << info.imageFileName << info.studentName;
        return out;
    }
};

#endif // PARTICIPANTINFO_H
