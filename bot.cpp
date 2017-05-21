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

void Bot::start(){
    this->groupsNames = readGroups();
    this->updateThread->start();
}

void Bot::analyze(Update *update){
    QString responseString;
    QString sendTo = QString::number(update->message.from.id);

    if(update->message.string == "/start"){
        responseString = "Hello,"+update->message.from.firstname+"!";
    }
    else if(update->message.string == "/timetable" ){
        responseString = "Please, send group number.";
    }
    else if(isGroup(update->message.string)){
        QByteArray schedule = this->netManager->getTimetable("21366");
        responseString = "Timetable.";
    }
    else{
         responseString = "Sorry, I don`t understand you.";
    }

    netManager->postRequest(ENDPOINT_SEND_MESSAGE,
                            "chat_id="+sendTo+"&text="+responseString);
}

bool Bot::isGroup(QString text){
    for(int i=0; i<text.size(); i++){
        if(text.at(i)<'0'||text.at(i)>'9')
           return false;
    }
    return true;
}

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
