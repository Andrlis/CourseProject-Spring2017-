#include "update.h"

Update::Update(QJsonObject update)
{
    id = update.value("update_id").toInt();
    message = Message(update.value("message").toObject());
}
