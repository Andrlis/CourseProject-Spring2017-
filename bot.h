#ifndef BOT_H
#define BOT_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMutex>
#include <QWaitCondition>
#include <QXmlStreamReader>
#include <QCoreApplication>

#include "requestmanager.h"
#include "updatethread.h"
#include "update.h"
#include "timetable.h"
#include "external.h"
#include "mysql_db.h"

#define BOT_TOKEN "<token>"

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
    MySQL_DB sqlDB;
    QMap<QString, QString> groupsNames;
    QMap<quint32, QString> user_Request;
    int updatesCount = 0;

    void analyze(Update *update);
    bool isGroup(QString text);
    QMap<QString, QString> readGroups();
    Timetable parseTimetable(QString id);
};

#endif // BOT_H
