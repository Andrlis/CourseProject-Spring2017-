#include "bot.h"

Bot::Bot()
{
    netManager=new RequestManager(BOT_TOKEN);
    updateThread = new UpdateThread(BOT_TOKEN, &updateList, &updatesCount);
}

Bot::~Bot(){
    delete netManager;
    delete updateThread;
}

/**
 * Analize update`s list and send response.
 * @brief Bot::botLogic
 */
void Bot::botLogic()
{
   Update currentUpdate;

   while(1){

       qMutex.lock();
       while(updatesCount == 0)
           listIsNotEmpty.wait(&qMutex);
       if(updatesCount>0){
       currentUpdate = this->updateList.at(0);
       this->updateList.removeAt(0);
       this->updatesCount--;
       }
       qMutex.unlock();

       analyze(&currentUpdate);
   }
}

/**
 * Get groups` id and
 * start thread, wich gets updates from telegrams server.
 * @brief Bot::start
 */
void Bot::start(){
    this->groupsNames = readGroups();
    this->updateThread->start();
}

/**
 * Analize update and send response to user
 * @brief Bot::analyze
 * @param update
 */
void Bot::analyze(Update *update){
    QString responseString;
    QString sendTo = QString::number(update->message.from.id);

    if(update->message.string == "/start"){
        user_Request.insert(update->message.from.id, update->message.string);
        responseString = "Приветствую, "+update->message.from.firstname+"!";
    }
    else if(update->message.string.contains("timetable")){
        user_Request.insert(update->message.from.id, update->message.string);
        responseString = "Пожалуйста, введите номер группы.";
    }
    else if(isGroup(update->message.string)){
        Timetable timetable;
        if(groupsNames.contains(update->message.string)){
            timetable = parseTimetable(groupsNames.value(update->message.string));
            if(user_Request.value(update->message.from.id)=="/timetable")
                responseString = timetable.all();
            else if(user_Request.value(update->message.from.id)=="/daytimetable")
                responseString = timetable.dayTimetable();
            else if(user_Request.value(update->message.from.id)=="/weektimetable")
                responseString = timetable.weekTimetable();
        }
        else
            responseString = "Простите, но такой группы не существует.";
    }
    else{
         responseString = "Простите, я не понимаю Вас.";
    }

    netManager->postRequest(ENDPOINT_SEND_MESSAGE,
                            "chat_id="+sendTo+"&text="+responseString);
}

/**
 * Check, is message a group number.
 * @brief Bot::isGroup
 * @param text
 * @return
 */
bool Bot::isGroup(QString text){
    for(int i=0; i<text.size(); i++){
        if(text.at(i)<'0'||text.at(i)>'9'||i>5)
           return false;
    }
    return true;
}

/**
 * Parse xml, wich contains groups` id.
 * @brief Bot::readGroups
 * @return
 */
QMap<QString, QString> Bot::readGroups(){
    QMap<QString, QString> groupMap;
    QString name;
    QString id;

    QXmlStreamReader xmlReader(netManager->getGroups());

    if(xmlReader.readNextStartElement()){
        if (xmlReader.name() == "studentGroupXmlModels"){
             while(xmlReader.readNextStartElement()){
                 if(xmlReader.name() == "studentGroup"){
                    while(xmlReader.readNextStartElement()){
                        if(xmlReader.name() == "id"){
                            id = xmlReader.readElementText();
                        }
                        else if(xmlReader.name() == "name"){
                            name = xmlReader.readElementText();
                        }
                        else
                            xmlReader.skipCurrentElement();
                    }
                    groupMap.insert(name, id);
                  }
                  else
                    xmlReader.skipCurrentElement();
             }
        }
    }
    return groupMap;
}

/**
 * Parse xml, wich contains timetable.
 * @brief Bot::parseTimetable
 * @param id
 * @return
 */
Timetable Bot::parseTimetable(QString id){
    Timetable timetable;

    timetable.currentWeek=netManager->getWeek();

    QXmlStreamReader xmlReader(netManager->getTimetable(id));

    if(xmlReader.readNextStartElement()){
        if (xmlReader.name() == "scheduleXmlModels"){
             while(xmlReader.readNextStartElement()){
                 if(xmlReader.name() == "scheduleModel"){
                    DayTimetable day;
                    while(xmlReader.readNextStartElement()){
                        if(xmlReader.name() == "schedule"){
                            Lesson lesson;
                            while(xmlReader.readNextStartElement()){
                                if(xmlReader.name() == "auditory"){
                                    lesson.classroom=xmlReader.readElementText();
                                }
                                else if(xmlReader.name() == "lessonTime"){
                                    lesson.time=xmlReader.readElementText();
                                }
                                else if(xmlReader.name() == "lessonType"){
                                    lesson.lessonType=xmlReader.readElementText();
                                }
                                else if(xmlReader.name() == "numSubgroup"){
                                    lesson.subGroup=xmlReader.readElementText();
                                }
                                else if(xmlReader.name() == "subject"){
                                    lesson.lessonName=xmlReader.readElementText();
                                }
                                else if(xmlReader.name() == "weekNumber"){
                                    lesson.weeks.append(xmlReader.readElementText());
                                }
                                else
                                    xmlReader.skipCurrentElement();
                            }
                            day.lessons.append(lesson);
                        }
                        else
                            xmlReader.skipCurrentElement();
                        }
                    timetable.days.append(day);
                 }
                 else
                     xmlReader.skipCurrentElement();
             }
         }
    }
    return timetable;
}
