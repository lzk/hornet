#include <QCoreApplication>
#include "commonapi.h"
#include "appconfig.h"
#include <signal.h>
#include "watcher.h"
#include <QTextCodec>
void quit(int)
{
    LOGLOG("SIGINT quit");
    if(qApp)
        qApp->quit();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
#if QT_VERSION < 0x050000
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
#endif

    signal(SIGINT ,quit);
    signal(SIGHUP ,quit);

    if(AppConfig::initConfig()){
        LOGLOG("\t\tThere has been a same app running!");
        return 0;
    }

    Watcher* watcher = new Watcher;
    watcher->start();

    int ret = a.exec();
    delete watcher;
    AppConfig::exit_app();
    LOGLOG("app exit!");
    return ret;
}
