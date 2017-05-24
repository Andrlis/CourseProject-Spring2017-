#include "timetable.h"

Timetable::Timetable(){
    date=QDate::currentDate();
}

QString Timetable::all(){
    QString string;
    string+="Текущая неделя: "+currentWeek+"\n";
    for(int i=0;i<days.size();i++){
        string+=days[i].toString();
    }
    string+="\nhttps://goo.gl/FR8ir8";
    return string;
}

QString Timetable::dayTimetable(){
    QString string;
    int day = date.dayOfWeek();
    if(day-1<days.size())
        string+=days[day-1].current(this->currentWeek);
    else
        string+="Сегодня занятий нет";
    return string;
}

QString Timetable::weekTimetable(){
    QString string;
    string+="Текущая неделя: "+currentWeek+"\n";
    for(int i=0;i<days.size();i++){
        string+=days[i].current(this->currentWeek);
    }
    string+="\nhttps://goo.gl/FR8ir8";
    return string;
}
