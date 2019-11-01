#include "appserver.h"
#include "commonapi.h"
#include "jkinterface.h"
#include "appconfig.h"
#include <unistd.h>
#include <QUrl>
#if QT_VERSION > 0x050000
#include <QUrlQuery>
#endif
#include "filterlib.h"
#include "filtercommon.h"
#include "filterjobhistory.h"

static void start_uiexe()
{
    //start tjgd1zsmui
//    const char* app_locker_file = LOCKER_UI;
    FileLocker app_file_locker;
    if(!app_file_locker.trylock(LOCKER_UI)){
        app_file_locker.unlock();
//        LOGLOG("uiexe not locked!");
        pid_t pid = fork();
        switch(pid)
        {
        case -1:
            LOGLOG("fork %s failed:" ,EXE_UI_NAME);
            exit(1);
            break;
        case 0:
#ifdef DEBUG_DEBUG
            execl(QString("/tmp/%1").arg(EXE_UI_NAME).toLatin1().constData() ,EXE_UI_NAME ,"-hide" ,0);
#else
            execlp(EXE_UI_NAME ,EXE_UI_NAME ,"-hide" ,0);
#endif
            exit(0);
            break;
        default:
            break;
        }
    }
}

AppServer::AppServer(const char* server_path ,QObject *parent)
    : QObject(parent)
    ,server_path(server_path)
{
    thread_server = new ServerThread(server_path);
    connect(thread_server ,SIGNAL(client_connect(int)) ,this ,SLOT(client_connect(int)));
    connect(thread_server ,SIGNAL(client_cmd(QString ,void*)) ,this ,SLOT(client_cmd(QString ,void*)));
    thread_server->start();
}

AppServer::~AppServer()
{
    delete thread_server;
}

void AppServer::restart_server()
{
    delete thread_server;

    LOGLOG("restart server:%s" ,server_path.toLatin1().constData());
    thread_server = new ServerThread(server_path.toLatin1().constData());
    connect(thread_server ,SIGNAL(client_connect(int)) ,this ,SLOT(client_connect(int)));
    connect(thread_server ,SIGNAL(client_cmd(QString ,void*)) ,this ,SLOT(client_cmd(QString ,void*)));
    thread_server->start();
}

int trans_the_buffer(char* buffer ,int bufsize)
{
    Trans_Client tc(SERVICE_TRANS_PATH);
    tc.writeThenRead(buffer ,bufsize);
    LOGLOG("filter cmd return is:%s" ,buffer);
}

static int callback_Server(void* para ,char* buffer,int bufsize)
{
    LOGLOG("filter cmd is:%s" ,buffer);
//    AppServer* app_server = (AppServer*)para;
    QUrl url(buffer);
    int jobid;
#if QT_VERSION > 0x050000
    jobid = QUrlQuery(QUrl(url)).queryItemValue("jobid").toInt();
#else
    jobid = QUrl(url).queryItemValue("jobid").toInt();
#endif
    QString cmd;
//    cmd = url.scheme();
//    QString printer = url.host(QUrl::PrettyDecoded);
    QString str(buffer);
    int index;
    index = str.indexOf("://");
    cmd = str.left(index);
//    LOGLOG("cmd is:%s" ,cmd.toLatin1().constData());
    QString printer = QString(buffer).mid(index + strlen("://"));
    index = printer.indexOf('?');
    if(index > 0)
        printer = printer.left(index);
    LOGLOG("printer is:%s" ,printer.toUtf8().constData());
    LOGLOG("jobid is:%d" ,jobid);

    if(!cmd.compare("start")){
        trans_the_buffer(buffer ,bufsize);
    }else if(!cmd.compare("check")){

        int status = filter_get_status(jobid);
        switch(status){
        case Filterlib_Status_Cancel:
            strcpy(buffer ,"cancel");
            break;
        case Filterlib_Status_timeout:
            strcpy(buffer ,"timeout");
            break;
        case Filterlib_Status_checking:
            strcpy(buffer ,"checking");
            break;
        case Filterlib_Status_OK:
            strcpy(buffer ,"ok");
            break;
        case Filterlib_Status_authorize_fail:
            strcpy(buffer ,"fail");
            break;
        case Filterlib_Status_invalidJobid:
        default:
            strcpy(buffer ,"invalid");
            break;
        }

    }else if(!cmd.compare("result")){

        int result;
        QString username,filename;
#if QT_VERSION > 0x050000
        result = QUrlQuery(QUrl(url)).queryItemValue("status").toInt();
        username = QUrlQuery(QUrl(url)).queryItemValue("username");
        filename = QUrlQuery(QUrl(url)).queryItemValue("filename");
#else
        result = QUrl(url).queryItemValue("status").toInt();
        username = QUrl(url).queryItemValue("username");
        filename = QUrl(url).queryItemValue("filename");
#endif
        LOGLOG("result is:%d" ,result);
        LOGLOG("username is:%s" ,username.toLatin1().constData());
        LOGLOG("filename is:%s" ,filename.toLatin1().constData());

        filterlib_struct fls;
        fls.jobid = jobid;
        fls.status = result;
        strcpy(fls.printername ,printer.toUtf8().constData());
        strcpy(fls.username ,username.toUtf8().constData());
        strcpy(fls.filename ,filename.toUtf8().constData());
        FilterJobHistory::save_job_history(&fls);

        trans_the_buffer(buffer ,bufsize);
    }

    return 0;
}

void AppServer::client_connect(int fd)
{
    thread_server->get_trans_server()->readThenWrite(fd ,callback_Server ,this);
}

void AppServer::client_cmd(const QString & ,void* )
{

}

