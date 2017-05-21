#include <QCoreApplication>
#include "requestmanager.h"
#include "bot.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Bot *bot = new Bot();
    bot->start();
    bot->botLogic();

    return a.exec();
}
