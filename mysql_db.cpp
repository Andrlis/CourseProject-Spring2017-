#include "mysql_db.h"

MySQL_DB::MySQL_DB(){}

void MySQL_DB::connect(){
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("telegarmbot");
    db.setUserName("root");
    db.setPassword("root");
    if (db.open())
        qDebug() << "MySQL:: Success";
    else
        qDebug() << "MySQL:: Failed to connect";
    //qDebug() << QSqlDatabase::drivers();
}
