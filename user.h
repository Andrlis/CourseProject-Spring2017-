#ifndef USER_H
#define USER_H

#include <QDebug>
#include <QString>
#include <QJsonObject>


class User
{
public:
    User() : id(0), firstname(QString()), lastname(QString()), username(QString()) {}
    User(QJsonObject user);

    quint32 id;
    QString firstname;
    QString lastname;
    QString username;
};

#endif // USER_H
