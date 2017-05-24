#ifndef BOT_H
#define BOT_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMutex>
#include <QWaitCondition>
#include <QXmlStreamReader>

#include "requestmanager.h"
#include "updatethread.h"
#include "update.h"
#include "timetable.h"
#include "external.h"

#define BOT_TOKEN "325691058:AAF9euS7KADAaSp3KUcScXIO4mLUsX28OcU"

class Bot: public QObject
{
 Q_OBJECT
public:
    explicit Bot();
    ~Bot();

    void botLogic();
    void start();
private:
    RequestManager *netManager;
    QList<Update> updateList;
    UpdateThread *updateThread;
    QMap<QString, QString> groupsNames;
    QMap<quint32, QString> user_Request;
    int updatesCount = 0;

    void analyze(Update *update);
    bool isGroup(QString text);
    QMap<QString, QString> readGroups();
    Timetable parseTimetable(QString id);    
};

#endif // BOT_H
