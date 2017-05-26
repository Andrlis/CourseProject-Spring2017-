#ifndef MYSQL_DB_H
#define MYSQL_DB_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QList>
#include <QString>
#include <QByteArray>
#include <string>

#include "note.h"

class MySQL_DB
{
public:
    MySQL_DB();

    void connect();
    void addNote(QString note, quint32 user_id);
    QList<Note> getNotes(quint32 user_id);
    void deleteNote(int note_id);

   QString crypt(QString strInput, QString strPassword);
   QString deCrypt(QString strInput, QString strPassword);

private:
    QSqlDatabase db;
};

#endif // MYSQL_DB_H
