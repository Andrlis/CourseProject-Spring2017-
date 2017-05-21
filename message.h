#ifndef MESSAGE_H
#define MESSAGE_H


#include <QDebug>

#include <QString>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>

//#include "contact.h"

#include "chat.h"
#include "user.h"


class Message
{
public:
    Message() {}
    Message(QJsonObject message);

    /**
     * @brief Telegram message events
     */
    enum MessageType {TextType, ContactType};

    // required
    quint32 id;
    QDateTime date;
    Chat chat;

    // optional
    User from;
    Message *replyToMessage;

    MessageType type;

    // payload
    QString string;
    User user;

    bool boolean;
};


#endif // MESSAGE_H
