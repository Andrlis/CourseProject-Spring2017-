#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H

#include <QThread>
#include <QJsonDocument>
#include <QWaitCondition>
#include <QJsonObject>
#include <QJsonArray>
#include <QMutex>
#include "update.h"
#include "requestmanager.h"
#include "external.h"

class UpdateThread: public QThread
{
    Q_OBJECT
public:
    UpdateThread(QString token, QList<Update> *updateList, int *updatesCount);
    ~UpdateThread();
    void getUpdates();
protected:
    void run();
private:
    QString token;
    QList<Update> *updateList;
    RequestManager *manager;
    int *updatesCount;
    quint32 lastUpdateID;


    QJsonObject jsonObjectFromByteArray(QByteArray json);
    QJsonArray jsonArrayFromByteArray(QByteArray json);
};

#endif // UPDATETHREAD_H
