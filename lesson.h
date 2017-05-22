#ifndef SUBJECT_H
#define SUBJECT_H

#include <QString>
#include <QList>

class Lesson
{
public:
    Lesson();
    QString toString();

    QString lessonName;
    QString time;
    QString classroom;
    QString lessonType;
    QString subGroup;
    QList<QString> weeks;
};

#endif // SUBJECT_H
