#ifndef DAYTIMETABLE_H
#define DAYTIMETABLE_H

#include <QList>

#include "lesson.h"

class DayTimetable
{
public:
    DayTimetable();
    QString toString();

    QString day;
    QList<Lesson> lessons;
};

#endif // DAYTIMETABLE_H
