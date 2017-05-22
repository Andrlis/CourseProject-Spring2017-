#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QList>

#include "daytimetable.h"

class Timetable
{
public:
    Timetable();
    QString toString();

    QString currentWeek;
    QList<DayTimetable> days;
};

#endif // TIMETABLE_H
