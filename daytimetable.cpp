#include "daytimetable.h"

/**
 * Return all lessons.
 * @brief DayTimetable::toString
 * @return
 */
QString DayTimetable::toString(){
    QString string;
    for(int i=0; i<lessons.size();i++){
        string+=lessons[i].toString();
    }
    string+="\n";
    return string;
}

/**
 * Return current day lessons
 * @brief DayTimetable::current
 * @param week
 * @return
 */
QString DayTimetable::current(QString week){
    QString string;
    for(int i=0; i<lessons.size();i++){
        if(lessons[i].weeks.contains(week))
            string+=lessons[i].current();
    }
    string+="\n";
    return string;
}
