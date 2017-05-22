#include "timetable.h"

Timetable::Timetable()
{

}

QString Timetable::toString(){
    QString string;
    string+="Текущая неделя: "+currentWeek+"\n";
    for(int i=0;i<days.size();i++){
        string+=days[i].toString();
    }
    string+="\nhttps://goo.gl/FR8ir8";
    return string;
}
