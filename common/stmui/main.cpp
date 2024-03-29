#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include "uinterface.h"
UInterface* gUInterface;
#include <sys/wait.h>
#include "uiconfig.h"
#include "commonapi.h"
#include "statusthread.h"
void quit(int)
{
    LOGLOG("SIGINT quit");
    if(qApp)
        qApp->quit();
}

int main(int argc, char *argv[])
{
    signal(SIGINT ,quit);
#ifdef Q_WS_X11
    qputenv("LIBOVERLAY_SCROLLBAR", 0);
#endif
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/image/app_icon.png"));
    a.setQuitOnLastWindowClosed(false);

//    QCoreApplication::setOrganizationName("TOEC");
//    QCoreApplication::setOrganizationDomain("mysoft.com");
//    QCoreApplication::setApplicationName("Status Monitor");

#if QT_VERSION < 0x050000
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
#endif

    QStringList arguments = QCoreApplication::arguments();
    if(arguments.contains("-test")){
        use_status_thread = false;
        testmode = true;
    }

    if(UIConfig::initConfig()){
        LOGLOG("\t\tThere has been a same app running!");
        return 0;
    }

    //worker run first,then show ui
    gUInterface = new UInterface;

    MainWindow* w = new MainWindow;
//    w->setWindowIcon(QIcon(":/image/app_icon.png"));

    if(!arguments.contains("-hide"))
        w->show();

    int ret = a.exec();
    delete w;
    delete gUInterface;
    UIConfig::exit_app();
    return ret;
}
