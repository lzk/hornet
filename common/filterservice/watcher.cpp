#include "watcher.h"
#include "appserver.h"
#include "appconfig.h"
#include "commonapi.h"
#include "filterjobhistory.h"
extern AppServer* app_server;
Watcher::Watcher(QObject *parent)
    : QThread(parent)
    ,abort(false)
{
    connect(this ,SIGNAL(server_restart()) ,app_server ,SLOT(restart_server()));

}

Watcher::~Watcher()
{
    abort = true;
    while(abort)usleep(1000);
}

void Watcher::run()
{
    forever{
        if (abort)
            break;
        watcher_job();
        usleep(1000*1000);
    }
    abort = false;
}

void Watcher::watcher_job()
{
    static int count = 0;
    if(count % 10 == 0){
//        if(!is_app_running(SERVER_PATH))
//            server_restart();
#ifndef Q_OS_MACX
        system("xset -dpms");//
#endif
    }

    if(count % 30 == 0){

        //update job history info
       FilterJobHistory::update_job_history();
       FilterJobHistory::update_fw_job_history();
    }
    count ++;
    if(count == 60)
        count = 0;
}
