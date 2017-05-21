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

#define ENDPOINT_GET_ME                     "getMe"
#define ENDPOINT_SEND_MESSAGE               "sendMessage"
#define ENDPOINT_FORWARD_MESSAGE            "forwardMessage"
#define ENDPOINT_SEND_PHOTO                 "sendPhoto"
#define ENDPOINT_SEND_AUDIO                 "sendAudio"
#define ENDPOINT_SEND_DOCUMENT              "sendDocument"
#define ENDPOINT_SEND_STICKER               "sendSticker"
#define ENDPOINT_SEND_VIDEO                 "sendVideo"
#define ENDPOINT_SEND_VOICE                 "sendVoice"
#define ENDPOINT_SEND_LOCATION              "sendLocation"
#define ENDPOINT_SEND_CHAT_ACTION           "sendChatAction"
#define ENDPOINT_GET_USER_PROFILE_PHOTOS    "getUserProfilePhotos"
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
    QUrl buildUrl(QString command);


private:
    QNetworkAccessManager *manager;
    QUrl url;
    QNetworkRequest request;
    QString token;
};

#endif // REQUESTMANAGER_H
