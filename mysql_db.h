#ifndef MYSQL_DB_H
#define MYSQL_DB_H

#include <QSqlDatabase>
#include <QDebug>

class MySQL_DB
{
public:
    MySQL_DB();

    void connect();
private:
    QSqlDatabase db;
};

#endif // MYSQL_DB_H
