QT += core
QT -= gui
QT += network
QT += sql

CONFIG += c++11

TARGET = BSUIR_Timetable
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    requestmanager.cpp \
    bot.cpp \
    update.cpp \
    user.cpp \
    message.cpp \
    chat.cpp \
    updatethread.cpp \
    external.cpp \
    timetable.cpp \
    daytimetable.cpp \
    lesson.cpp \
    mysql_db.cpp \
    note.cpp

HEADERS += \
    requestmanager.h \
    bot.h \
    update.h \
    user.h \
    message.h \
    chat.h \
    updatethread.h \
    external.h \
    timetable.h \
    daytimetable.h \
    lesson.h \
    mysql_db.h \
    note.h
