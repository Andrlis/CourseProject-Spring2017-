#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QByteArray>
#include <QEventLoop>

#define ENDPOINT_SEND_MESSAGE               "sendMessage"
#define ENDPOINT_GET_UPDATES                "getUpdates"
#define ENDPOINT_SET_WEBHOOK                "setWebhook"
#define ENDPOINT_GET_FILE                   "getFile"

#define API_HOST "api.telegram.org"

class RequestManager: public QObject
{
    Q_OBJECT
public:
    explicit RequestManager(QString token, QObject *parent = 0);
    ~RequestManager();
    QByteArray postRequest(QString command, QString postData = "");
    QByteArray getRequest(QString command);
    QByteArray getTimetable(QString groupId);
    QByteArray getGroups();
    QByteArray getWeek();
    QUrl buildUrl(QString command);


private:
    QNetworkAccessManager *manager;
    QUrl url;
    QNetworkRequest request;
    QString token;
};

#endif // REQUESTMANAGER_H
