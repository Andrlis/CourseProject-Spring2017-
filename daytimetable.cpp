#include "daytimetable.h"

DayTimetable::DayTimetable()
{

}

QString DayTimetable::toString(){
    QString string;
    for(int i=0; i<lessons.size();i++){
        string+=lessons[i].toString();
    }
    string+="\n";
    return string;
}
