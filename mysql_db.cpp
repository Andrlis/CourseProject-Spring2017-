#include "mysql_db.h"

MySQL_DB::MySQL_DB(){}

void MySQL_DB::connect(){
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("telegrambot");
    db.setUserName("root");
    db.setPassword("root");
    if (!db.open())
        qDebug() << "MySQL:: Failed to connect.";
}

/**
 * Get user`s notes from DB.
 * @brief MySQL_DB::getNotes
 * @param user_id
 * @return
 */
QList<Note> MySQL_DB::getNotes(quint32 user_id){
    QList<Note> notes;
    QSqlQuery query("SELECT note_id, user_id, note FROM users_notes WHERE user_id='"+QString::number(user_id)+"'");
    if(!query.isActive())
        qDebug() << "MySQL:: Error. getNotes";
    else{
        Note note;
        while(query.next()){
            note.note_id = query.value(0).toInt();
            note.noteText = deCrypt(query.value(2).toString(),QString::number(user_id));


            notes.append(note);
        }
    }
    return notes;
}

/**
 * Add new note to DB.
 * @brief MySQL_DB::addNote
 * @param note
 * @param user_id
 */
void MySQL_DB::addNote(QString note, quint32 user_id){
    QSqlQuery query;
    query.prepare("INSERT INTO users_notes (note_id, user_id, note)"
                                        "VALUES(NULL, ?, ?)");
    query.addBindValue(user_id);
    query.addBindValue(crypt(note,QString::number(user_id)));
    query.exec();
}

/**
 * Delete selected note from DB.
 * @brief MySQL_DB::deleteNote
 * @param note_id
 */
void MySQL_DB::deleteNote(int note_id){
    QSqlQuery query;
    query.prepare("DELETE FROM users_notes WHERE note_id='"+QString::number(note_id)+"'");
    query.exec();
}

QString MySQL_DB::crypt(QString strInput, QString strPassword)
{
    int i,j;
    QString strOutput="";

    // Перевод строк в битовые массивы с использованием локальных таблиц
    QByteArray baInput    = strInput.toLocal8Bit();
    QByteArray baPassword = strPassword.toLocal8Bit();

    // Кодирование информации
    for (i=0; i < baInput.size(); i++)
    {
        for (j=0; j < baPassword.size(); j++)
        {
            // XOR - кодировка символа
            baInput[i] = baInput[i] ^ (baPassword[j] + (i*j));
        }

        //Преобразование числа в шестнадцатеричную систему
        strOutput += QString("%1").arg((int)((unsigned char)baInput[i]),2,16,QChar('0'));
    }

    //Возврат кодированной строки
    return strOutput;
}


// Декодирование строки
QString MySQL_DB::deCrypt(QString strInput, QString strPassword)
{
    int i,j;

    // Декодировка строки из 16-ричной системы в битовый массив
    QByteArray baInput    = QByteArray::fromHex(strInput.toLocal8Bit());
    // Перевод строки пароля в битовый массив
    QByteArray baPassword = strPassword.toLocal8Bit();

    // Декодирование информации
    for (i=0; i < baInput.size(); i++)
    {
        for (j=0; j < baPassword.size(); j++)
        {
            // XOR - кодировка символа
            baInput[i] = baInput[i] ^ (baPassword[j] + (i*j));
        }
    }

    //Возврат кодированной строки
    return QString::fromLocal8Bit(baInput.data());
}

