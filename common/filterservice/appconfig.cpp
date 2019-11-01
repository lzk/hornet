#include "appconfig.h"
#include "appserver.h"
#include "commonapi.h"
#include <unistd.h>

//const QString app_name = QString::fromUtf8("打印机状态监视器");
FileLocker app_file_locker;
AppServer* app_server;

//extern
//int (* getpidvid)(const QString& modelname ,int* pid ,int* vid);
//log file var
extern const char* log_app_name;
extern const char* app_version;
//usb error control var
static bool _isDeviceSupported(Printer_struct* ps)
{
//    LOGLOG("tomcat found device name:%s \n\tmodel:%s" ,ps->name,ps->makeAndModel);

    QString makeAndModel(ps->makeAndModel);
    if(0){
#ifdef DEBUG_DEBUG
    }else if(makeAndModel.startsWith("Lenovo L100DW")){
        return true;
    }else if(makeAndModel.startsWith("Lenovo L100W")){
        return true;
    }else if(makeAndModel.startsWith("Lenovo L100D")){
        return true;
    }else if(makeAndModel.startsWith("Lenovo L100")){
        return true;
    }else if(makeAndModel.startsWith("Lenovo M100W")){
        return true;
    }else if(makeAndModel.startsWith("Lenovo M100D")){
        return true;
    }else if(makeAndModel.startsWith("Lenovo M100")){
        return true;
    }else if(makeAndModel.startsWith("Lenovo M101DW")){
        return true;
    }else if(makeAndModel.startsWith("Lenovo M101W")){
        return true;
    }else if(makeAndModel.startsWith("Lenovo M101")){
        return true;
    }else if(makeAndModel.startsWith("Lenovo M102W")){
        return true;
    }else if(makeAndModel.startsWith("Lenovo M102")){
        return true;
    }else if(makeAndModel.startsWith("Lenovo M7268W")){
        return true;
    }else if(makeAndModel.startsWith("AXY KS1352")){
        return true;
#endif
    }else if(makeAndModel.startsWith("CCT HS1610d")){
        return true;
    }
    return false;
}

//static int _getpidvid(const QString& makeAndModel ,int* pid ,int* vid)
//{
//    if(!pid || !vid)
//        return -1;
//    *vid = 0x0efd;
//    *pid = -1;
//    if(makeAndModel.startsWith("toec/OEP3300CDN")){
//        *pid = 0x002c;
//    }
//    return (*pid == -1) ?-1 :0;
//}

AppConfig::AppConfig(QObject *parent) :
    QObject(parent)
{
}

extern const char* log_file;
int AppConfig::initConfig()
{
    log_app_name = EXE_NAME;
    app_version = APP_VERSION;
    log_file = LOG_FILE_NAME;
    log_init();
    if(app_file_locker.trylock(LOCKER_EXE)){
        LOGLOG("app had been locked!");
        return -1;
    }
//    if(is_app_running(SERVER_PATH)){
//        LOGLOG("socket working!");
//        return -2;
//    }

    LOGLOG("--------%s v%s-------" ,log_app_name ,app_version);
#ifndef DEBUG_DEBUG
    //release as deaemon
    int result = daemon(0 ,0);
    if(!result){
        LOGLOG("daemon success!");
    }
#endif

    g_config_file =  CONFIG_FILE;

    //config status server thread
#ifdef DEBUG_DEBUG
//    if(testmode){
        status_file = TEST_STATUS_FILE;
        status_lock_file = TEST_STATUS_LOCKER_FILE;
#else
//    }else{
        status_file = STATUS_FILE;
        status_lock_file = STATUS_LOCKER_FILE;
//    }
#endif
//    ui_server_path = SERVER_PATH;

    //config tomcat supported printer model
    isDeviceSupported = _isDeviceSupported;
//    getpidvid = _getpidvid;

    app_server = new AppServer(SERVER_PATH);
    return 0;
}

#include <QFile>
void AppConfig::exit_app()
{
//    QFile::remove(status_file);
//    QFile::remove(status_lock_file);
    delete app_server;
    app_file_locker.unlock();
}
