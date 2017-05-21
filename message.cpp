#include "message.h"

Message::Message(QJsonObject message)
{
    id = message.value("message_id").toInt();
    date = QDateTime::fromMSecsSinceEpoch(message.value("date").toInt());
    chat = Chat(message.value("chat").toObject());


    if (message.contains("from")) {
        from = User(message.value("from").toObject());
    }
    if (message.contains("reply_to_message")) {
        replyToMessage = new Message(message.value("reply_to_message").toObject());
    }

    // Parse payload
    if (message.contains("text")) {
        string = message.value("text").toString();
        type = Message::TextType;
    }
}
