#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QList>
#include <QDate>

#include "daytimetable.h"

class Timetable
{
public:
    Timetable();
    QString all();
    QString dayTimetable();
    QString weekTimetable();

    QString currentWeek;
    QList<DayTimetable> days;

private:
     QDate date;
};

#endif // TIMETABLE_H
