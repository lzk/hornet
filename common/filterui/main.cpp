#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <signal.h>
#include "log.h"
#include "appconfig.h"
extern const char* log_app_name;
extern const char* app_version;
extern const char* log_file;
void quit(int)
{
    if(qApp)
        qApp->quit();
}


int main(int argc, char *argv[])
{
    signal(SIGINT ,quit);

    QApplication a(argc, argv);
//    a.setWindowIcon(QIcon(":/image/app_icon.png"));
    a.setQuitOnLastWindowClosed(false);

//    QCoreApplication::setOrganizationName("TOEC");
////    QCoreApplication::setOrganizationDomain("mysoft.com");
//    QCoreApplication::setApplicationName("FingerUi");
#if QT_VERSION < 0x050000
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
#endif

    log_app_name = EXE_NAME;
    app_version = APP_VERSION;
    log_file = LOG_FILE_NAME;
    log_init();

    QStringList arguments = QCoreApplication::arguments();
    QString str;
    if(arguments.count() < 2)
        str = "start://HS1610d?jobid=0&time_val=30";
    else
        str = arguments[1];
    MainWindow w(str);
    w.show();

    a.exec();
    return 0;
}
