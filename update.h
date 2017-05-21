#ifndef UPDATE_H
#define UPDATE_H

#include <QDebug>
#include <QJsonObject>
#include "message.h"

class Update
{
public:
    Update() {}
    Update(QJsonObject update);

    quint32 id;
    Message message;
};

#endif // UPDATE_H
