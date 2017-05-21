#ifndef CHAT_H
#define CHAT_H

#include <QDebug>
#include <QString>
#include <QJsonObject>

class Chat
{
public:
    Chat() {}
    Chat(QJsonObject chat);

    enum ChatType {
        Private, Group, Channel
    };

    quint32 id;
    ChatType type;
    QString title;
    QString username;
    QString firstname;
    QString lastname;
};



#endif // CHAT_H
