#include "lesson.h"

Lesson::Lesson()
{
    lessonName="";
    time="";
    lessonType="";
    classroom="";
}

QString Lesson::toString(){
    QString string;
    string = "%E2%9D%97"+time+"-"+lessonName+"("+lessonType+")-"+classroom;
    if(weeks.at(0)!="0"){
         string+="-(";
         for(int i=0; i<weeks.size();i++){
            string+=weeks.at(i)+" ";
         }
         string+="нед.)";
    }
    if(subGroup!="0")
        string+="-"+subGroup+"подгр.";
    string+="\n";
    return string;
}

QString Lesson::current(){
    QString string;
    string = "%E2%9D%97"+time+"-"+lessonName+"("+lessonType+")-"+classroom;
    if(subGroup!="0")
        string+="-"+subGroup+"подгр.";
    string+="\n";
    return string;
}
