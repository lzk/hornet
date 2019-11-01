#include "uiconfig.h"
#include "commonapi.h"
#include "filelocker.h"
#include <QFile>
#include <QSharedMemory>

bool testmode = false;
const QString app_name = QString::fromUtf8("打印机状态监视器");
FileLocker app_file_locker;

extern
int (* getpidvid)(const QString& modelname ,int* pid ,int* vid);
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

static int _getpidvid(const QString& makeAndModel ,int* pid ,int* vid)
{
    if(!pid || !vid)
        return -1;
    *vid = 0xf3f0;
    *pid = -1;
    if(0){
#ifdef DEBUG_DEBUG
    }else if(makeAndModel.contains("L100DW")){
        *pid = 0x5445;
        *vid = 0x17ef;
    }else if(makeAndModel.contains("L100W")){
        *pid = 0x5443;
        *vid = 0x17ef;
    }else if(makeAndModel.contains("L100D")){
        *pid = 0x5444;
        *vid = 0x17ef;
    }else if(makeAndModel.contains("L100")){
        *pid = 0x5442;
        *vid = 0x17ef;
    }else if(makeAndModel.contains("M100W")){
        *pid = 0x5641;
        *vid = 0x17ef;
    }else if(makeAndModel.contains("M100D")){
        *pid = 0x5644;
        *vid = 0x17ef;
    }else if(makeAndModel.contains("M100")){
        *pid = 0x563e;
        *vid = 0x17ef;
    }else if(makeAndModel.contains("M101DW")){
        *pid = 0x5645;
        *vid = 0x17ef;
    }else if(makeAndModel.contains("M101W")){
        *pid = 0x5642;
        *vid = 0x17ef;
    }else if(makeAndModel.contains("M101")){
        *pid = 0x563f;
        *vid = 0x17ef;
    }else if(makeAndModel.contains("M102W")){
        *pid = 0x5643;
        *vid = 0x17ef;
    }else if(makeAndModel.contains("M102")){
        *pid = 0x5640;
        *vid = 0x17ef;
    }else if(makeAndModel.contains("M7268W")){
        *pid = 0x563a;
        *vid = 0x17ef;
    }else if(makeAndModel.contains("LJ2310N")){
        *pid = 0x5459;
        *vid = 0x17ef;
    }else if(makeAndModel.contains("LJ2320DN")){
        *pid = 0x5454;
        *vid = 0x17ef;
    }else if(makeAndModel.contains("KS1352")){
        *pid = 0x1352;
#endif
    }else if(makeAndModel.contains("HS1610d")){
        *pid = 0x1611;
    }
    return (*pid == -1) ?-1 :0;
}

UIConfig::UIConfig(QObject *parent) :
    QObject(parent)
{
}

extern const char* log_file;
int UIConfig::initConfig()
{
    log_app_name = EXE_NAME;
    app_version = APP_VERSION;
    log_file = LOG_FILE_NAME;
    log_init();

//    QSharedMemory  shared;
////    shared.setKey(EXE_NAME);
//    shared.setNativeKey(EXE_NAME);
////    LOGLOG("\t\tshared attach:%s" ,shared.key().toUtf8().constData());
//    LOGLOG("\t\tshared attach:%s" ,shared.nativeKey().toUtf8().constData());
//    if(shared.attach())
//    {
////        LOGLOG("\t\tshared exist:%s" ,shared.key().toUtf8().constData());
//        LOGLOG("\t\tshared exist:%s" ,shared.nativeKey().toUtf8().constData());
//        return -1;
//    }
//    if(!shared.create(1)){
//        LOGLOG("\t\t%s" ,shared.errorString().toUtf8().constData());
//        return -1;
//    }
//    char* shdata = (char*)shared.data();
//    LOGLOG("\t\t share data address is :%x" ,shdata);

    if(app_file_locker.trylock(LOCKER_EXE)){
        LOGLOG("\t\tapp had been locked!");
        return -1;
    }
//    if(is_app_running(DOMAIN_UIEXE)){
//        LOGLOG("socket working!");
//        return -2;
//    }

    LOGLOG("--------%s v%s-------" ,log_app_name ,app_version);
    QString str;
    str = get_string_from_shell_cmd("uname -a");
    LOGLOG("%s" ,str.toLatin1().constData());
    str = get_string_from_shell_cmd("cat /etc/issue");
    LOGLOG("%s\n\n" ,str.toLatin1().constData());
//    str = get_string_from_shell_cmd("who" ,1);
//    LOGLOG("%s\n\n" ,str.toLatin1().constData());
//    str = get_string_from_shell_cmd("whoami");
//    LOGLOG("%s\n\n" ,str.toLatin1().constData());
//    str = get_string_from_shell_cmd("echo $DISPLAY");
//    LOGLOG("%s\n\n" ,str.toLatin1().constData());
//    LOGLOG("%s\n\n" ,getenv("DISPLAY"));

    g_config_file =  CONFIG_FILE;

    //config status server thread
    if(testmode){
        status_file = TEST_STATUS_FILE;
        status_lock_file = TEST_STATUS_LOCKER_FILE;
    }else{
        status_file = STATUS_FILE;
        status_lock_file = STATUS_LOCKER_FILE;
    }

//    ui_server_path = SERVER_PATH;

    //config tomcat supported printer model
    isDeviceSupported = _isDeviceSupported;
    getpidvid = _getpidvid;

//    app_server = new AppServer(DOMAIN_UIEXE);
    return 0;
}

void UIConfig::exit_app()
{
//    QFile::remove(status_file);
//    QFile::remove(status_lock_file);
    app_file_locker.unlock();
//    delete app_server;
}
