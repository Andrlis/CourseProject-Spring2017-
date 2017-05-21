#include "updatethread.h"

UpdateThread::UpdateThread(QString token, QList<Update> *updateList, int *updatesCount)
{
    this->token = token;
    this->updateList = updateList;
    this->updatesCount = updatesCount;
    this->lastUpdateID = 0;
}

UpdateThread::~UpdateThread(){
    delete updateList;
    delete manager;
}

/**
 * Get new updates from telegram`s server.
 * @brief UpdateThread::getUpdates
 */
void UpdateThread::getUpdates()
{
    QJsonArray json;
    if(this->lastUpdateID == 0)                                                          //if it`s first request
        json = this->jsonArrayFromByteArray(manager->getRequest(ENDPOINT_GET_UPDATES));
    else                                                                                 //set offset
        json = this->jsonArrayFromByteArray(manager->postRequest(ENDPOINT_GET_UPDATES,
                                                     "offset="+QString::number(this->lastUpdateID+1)));

    qMutex.lock();
    foreach (QJsonValue value, json) {
        this->updateList->append(Update(value.toObject()));
        *(this->updatesCount)=*(this->updatesCount)+1;
        this->lastUpdateID = this->updateList->last().id;
    }
    if(*(this->updatesCount)>0)
        listIsNotEmpty.wakeAll();
    qMutex.unlock();
}

/**
 * Parse server`s response from json.
 * @brief UpdateThread::jsonObjectFromByteArray
 * @param json
 * @return
 */
QJsonObject UpdateThread::jsonObjectFromByteArray(QByteArray json)
{
    QJsonDocument d = QJsonDocument::fromJson(json);
    QJsonObject obj = d.object();

    if (obj.isEmpty()) {
        qCritical("Got an empty response object");
        return obj;
    }

    if (obj.value("ok").toBool() != true) {
        qWarning("Result is not Ok");
        return obj;
    }

    return obj.value("result").toObject();
}

QJsonArray UpdateThread::jsonArrayFromByteArray(QByteArray json)
{
    QJsonDocument d = QJsonDocument::fromJson(json);
    QJsonObject obj = d.object();

    if (obj.isEmpty()) {
        qCritical("Got an empty response object");
        return QJsonArray();
    }

    if (obj.value("ok").toBool() != true) {
        qWarning("Result is not Ok");
        return QJsonArray();
    }

    return obj.value("result").toArray();
}

void UpdateThread::run(){
    this->manager = new RequestManager(token);
    while(1){
        getUpdates();
        sleep(10);
    }
}

