#ifndef DAYTIMETABLE_H
#define DAYTIMETABLE_H

#include <QList>

#include "lesson.h"

class DayTimetable
{
public:
    QString toString();
    QString current(QString week);

    QString day;
    QList<Lesson> lessons;
};

#endif // DAYTIMETABLE_H
