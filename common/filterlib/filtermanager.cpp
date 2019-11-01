#include "filtermanager.h"
#include "filterlibconfig.h"
#include "jkinterface.h"
#include <string.h>
#include <unistd.h>

FilterManager::FilterManager(filterlib_struct* para)
    :g_para(*para)
{

}
int FilterManager::authorize(filterlib_struct* para)
{
    if(!para)
        return -1;
    g_abort = false;

    Trans_Client tc(SERVER_PATH);
    char buffer[256];
    int result;
    int time_val = 30;

    sprintf(buffer ,"start://%s?jobid=%d" ,para->printername ,para->jobid);
    tc.writeThenRead(buffer ,sizeof(buffer));
    LOGLOG("filterlib: %s" ,buffer);
    if(!strcmp(buffer ,"start_noLogin")){
        LOGLOG("filterlib: no login when printing");
        return Filterlib_Status_OK;
    }else if(strstr(buffer ,"startok")== NULL){
        LOGLOG("filterlib: fail to start");
        return Filterlib_Status_Fail;
    }else{
        sscanf(buffer,"startok:%d",&time_val);
    }

    time_val += 10;//more 10 seconds to timeout
    for(int i = time_val ;i > 0 ;i--){
        if(g_abort){
            result = Filterlib_Status_Abort_Print;
            break;
        }
        sprintf(buffer ,"check://%s?jobid=%d" ,para->printername ,para->jobid);
        tc.writeThenRead(buffer ,sizeof(buffer));
        if(!strcmp(buffer ,"checking")){
//            result = Filterlib_Status_checking;
        }else if(!strcmp(buffer ,"cancel")){
            result = Filterlib_Status_Cancel;
            break;
        }else if(!strcmp(buffer ,"timeout")){
            result = Filterlib_Status_timeout;
            break;
        }else if(!strcmp(buffer ,"ok")){
            result = Filterlib_Status_OK;
            break;
        }else if(!strcmp(buffer ,"fail")){
            result = Filterlib_Status_authorize_fail;
            break;
        }else{
            result = Filterlib_Status_Fail;
            break;
        }
        if(i == 0){
            result = Filterlib_Status_timeout;
        }else{
            sleep(1);
        }
    }

    sprintf(buffer ,"result://%s?jobid=%d&status=%d&username=%s&filename=%s"
            ,para->printername ,para->jobid
           ,result ,para->username ,para->filename
            );
    tc.writeThenRead(buffer ,sizeof(buffer));
    if(!strcmp(buffer ,"resultok"))
    {
        LOGLOG("filterlib: result:%d" ,result);
    }
    return result;
}

int FilterManager::abort()
{
    int ret = 0;
    if(!g_abort)
        g_abort = true;
    else{
        filterlib_struct para = g_para;
        para.status = Filterlib_Status_Abort_Print;
        ret = result(&para);
    }
    return ret;
}

int FilterManager::result(filterlib_struct* para)
{
    if(!para)
        return -1;
    Trans_Client tc(SERVER_PATH);
    char buffer[256];
    sprintf(buffer ,"result://%s?jobid=%d&status=%d&username=%s&filename=%s"
            ,para->printername ,para->jobid ,para->status
            ,para->username ,para->filename);
    tc.writeThenRead(buffer ,sizeof(buffer));
    if(!strcmp(buffer ,"resultok"))
    {
        LOGLOG("filterlib: result ok");
    }
//    LOGLOG("filterlib: filterlib_result end");
    return 0;
}

#include <QString>
//static void callback_getJob(void* para,Job_struct* js)
//{
//    filterlib_struct* job = (filterlib_struct*)para;
//    if(js->id != job->jobid)
//        return;
//    LOGLOG("filter printer is:%s" ,job->printername);
//    LOGLOG("jobid printer is:%s" ,js->printer);
////    LOGLOG("jobid utf8 printer is:%s" ,QString::fromUtf8(js->printer).toUtf8().constData());

//}
#include <QVariant>
#include <QSettings>
static FilterManager* fm = NULL;
int FilterManager::filtermanager_job(filterlib_struct* para)
{
    LOGLOG("filterlib: filtermanager_job enter");
//    if(!para->username[0]){
//        strcpy(para->username ,"test printer");
//    }
//    if(!para->filename[0]){
//        strcpy(para->filename ,"test printer");
//    }
//    if(!para->printername[0]){
//        strcpy(para->printername ,"test printer");
//    }

    QString printername = QString::fromUtf8(para->printername);
//    LOGLOG("printer is:%s" ,printername.toUtf8().constData());

//    cups_get_job(callback_getJob ,(void*)para);

    int ret;
    bool is_login_when_printing;
    QVariant value;
    QSettings settings(CONFIG_FILE ,QSettings::NativeFormat);
    QString key = QString("%1/%2").arg(CONFIG_KEY_isLoginWhenPrinting).arg(printername);
    value = settings.value(key ,false);
    is_login_when_printing = value.toBool();
    LOGLOG("is printer:%s show login window:%d" ,para->printername ,is_login_when_printing);

    if(is_login_when_printing){
//    if(para->model && is_login_when_printing){
        if(!fm){
            fm = new FilterManager(para);
        }
        ret = fm->authorize(para);
    }else{
        para->status = Filterlib_Status_nologin_model;
        ret = FilterManager::result(para);
    }
    return ret;
}

int FilterManager::filtermanager_job_abort()
{
    if(fm){
        fm->abort();
    }
    return 0;
}

int FilterManager::filtermanager_job_exit()
{
    LOGLOG("filterlib: filtermanager_job exit");
    if(fm){
        delete fm;
        fm = NULL;
    }
//    LOGLOG("filterlib: test forever for not print");
//    while(1){
//        sleep(1);
//    }
    return 0;
}
