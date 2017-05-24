#include "requestmanager.h"

RequestManager::RequestManager(QString token, QObject *parent) : QObject(parent)
{
    // Инициализируем менеджер
    this->manager = new QNetworkAccessManager();
    this->token=token;
}

RequestManager::~RequestManager(){
    delete manager;
}

QByteArray RequestManager::getRequest(QString command)
{
    QEventLoop loop;
    QNetworkReply *reply;

    url = buildUrl(command);                             // URL, к которому будем получать данные
    request.setUrl(url);                                 // Устанавлвиваем URL в запрос
    reply = manager->get(request);                       // Выполняем запрос

    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
       loop.exec();

       if (reply->error()) {
           qDebug() << "ERROR";
           qDebug() << reply->errorString();
           delete reply;
           return QByteArray();
       }

       QByteArray ret = reply->readAll();
       delete reply;
       return ret;

}

QByteArray RequestManager::postRequest(QString command, QString postData)
{
    QEventLoop loop;
    QNetworkReply *reply;

    url = buildUrl(command);                             // URL, к которому будем получать данные
    request.setUrl(url);                                 // Устанавлвиваем URL в запрос
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    reply = manager->post(request,postData.toUtf8());            // Выполняем запрос

    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
       loop.exec();

       if (reply->error()) {
           qDebug() << "ERROR";
           qDebug() << reply->errorString();
           delete reply;
           return QByteArray();
       }

       QByteArray ret = reply->readAll();
       delete reply;
       return ret;
}

QByteArray RequestManager::getTimetable(QString groupId)
{
    QEventLoop loop;
    QNetworkReply *reply;

    url = QUrl();
    url.setScheme("https");
    url.setHost("www.bsuir.by");
    url.setPath("/schedule/rest/schedule/"+groupId);

    request.setUrl(url);                                 // Устанавлвиваем URL в запрос
    reply = manager->get(request);                       // Выполняем запрос

    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
       loop.exec();

       if (reply->error()) {
           qDebug() << "ERROR";
           qDebug() << reply->errorString();
           delete reply;
           return QByteArray();
       }

       QByteArray ret = reply->readAll();
       delete reply;
       return ret;
}

QByteArray RequestManager::getGroups()
{
    QEventLoop loop;
    QNetworkReply *reply;

    url = QUrl();
    url.setScheme("https");
    url.setHost("www.bsuir.by");
    url.setPath("/schedule/rest/studentGroup");

    request.setUrl(url);                                 // Устанавлвиваем URL в запрос
    reply = manager->get(request);                       // Выполняем запрос

    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
       loop.exec();

       if (reply->error()) {
           qDebug() << "ERROR";
           qDebug() << reply->errorString();
           delete reply;
           return QByteArray();
       }

       QByteArray ret = reply->readAll();
       delete reply;
       return ret;
}

QByteArray RequestManager::getWeek()
{
    QEventLoop loop;
    QNetworkReply *reply;

    url = QUrl();
    url.setScheme("https");
    url.setHost("www.bsuir.by");
    url.setPath("/schedule/rest/currentWeek/date/16.09.2016");

    request.setUrl(url);                                 // Устанавлвиваем URL в запрос
    reply = manager->get(request);                       // Выполняем запрос

    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
       loop.exec();

       if (reply->error()) {
           qDebug() << "ERROR";
           qDebug() << reply->errorString();
           delete reply;
           return QByteArray();
       }

       QByteArray ret = reply->readAll();
       delete reply;
       return ret;

}

QUrl RequestManager::buildUrl(QString command)
{
    QUrl url = QUrl();
    url.setScheme("https");
    url.setHost(API_HOST);
    url.setPath("/bot"+this->token+"/"+command);

    return url;
}

