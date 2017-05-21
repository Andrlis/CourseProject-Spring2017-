#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QList>

#include "daytimetable.h"

class Timetable
{
public:
    Timetable();

    QList<DayTimetable> days;

};

#endif // TIMETABLE_H
