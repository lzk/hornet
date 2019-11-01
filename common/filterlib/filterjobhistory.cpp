#include "filterjobhistory.h"
#include "jkinterface.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <QSettings>
#include <QMutex>
#include "pro_config.h"
static const char* job_history_file_name = JOBHISTORYFILE;
static const char* job_key ="jobs/id/";

static QMutex mutex;

enum{
    JobHistoryIndex_id,
    JobHistoryIndex_printername,
    JobHistoryIndex_hostname,
    JobHistoryIndex_username,
    JobHistoryIndex_filename,
    JobHistoryIndex_copies,
    JobHistoryIndex_result,
//    JobHistoryIndex_isFingerEnable,
//    JobHistoryIndex_isFingerChecked,
    JobHistoryIndex_pages,
    JobHistoryIndex_state,
    JobHistoryIndex_time,
    JobHistoryIndex_jobresult,

    JobHistoryIndex_max,
};

FilterJobHistory::FilterJobHistory()
{

}

static void callback_getJob(void* para,Job_struct* js)
{
    filterlib_struct* job = (filterlib_struct*)para;
    if(js->id != job->jobid)
        return;

    char hostname[256];
    gethostname(hostname ,sizeof(hostname));
//    StatusMonitor* sm = (StatusMonitor*)para;
    char job_history[512];

    sprintf(job_history ,"%d/\\%s/\\%s/\\%s/\\%s/\\%d/\\%d"
//            ,js->id ,js->printer ,hostname,js->user_name  ,js->name
            ,js->id ,job->printername ,hostname,job->username  ,job->filename
             ,(js->copies < 1) ?1 :js->copies
             ,job->status
//            ,job->is_finger_enable,job->is_finger_checked//是，成功
            );
//    sprintf(job_history ,"echo %s >> %s" ,job_history ,job_history_file_name);
//    system(job_history);

    char device_uri[256];
    int job_result = -1;
    cups_get_device_uri(js->printer ,device_uri);
    if(QString(device_uri).startsWith("usb://")){
        job_result = -2;
    }

    mutex.lock();
    QSettings settings(job_history_file_name ,QSettings::defaultFormat());
    QString key = QString().sprintf("%s%d/" ,job_key ,js->id);
    settings.setValue(key + "main" ,QString(job_history));
    settings.setValue(key + "pages" ,js->pages_completed);
    settings.setValue(key + "state" ,js->state);//JOBSTATE_COMPLETED?
    settings.setValue(key + "time" ,js->timet);
    settings.setValue(key + "job_result" ,job_result);
    settings.sync();
    mutex.unlock();
}
#include <QDateTime>
int FilterJobHistory::save_job_history(filterlib_struct* job)
{
#ifdef DEBUG_DEBUG
    Job_struct jbs;
    Job_struct* js = &jbs;
    js->id = job->jobid;
    js->copies = 1;
    js->pages_completed = 2;
    js->state = JOBSTATE_COMPLETED;
    js->timet = QDateTime::currentDateTime().toMSecsSinceEpoch();
    strcpy(js->printer ,job->printername);
    callback_getJob(job ,js);
#else
    cups_get_job(callback_getJob ,(void*)job);
#endif
    return 0;
}

bool sort_jobs(const QString &s1, const QString &s2)
{
    return s1.toInt() > s2.toInt();
}

int FilterJobHistory::get_job_history(QList<Job_history >& pJobs)
{
    mutex.lock();
    QSettings settings(job_history_file_name ,QSettings::defaultFormat());
    QString key(job_key);
    settings.beginGroup(key);
    QStringList jobs = settings.childGroups();
    settings.endGroup();

    qSort(jobs.begin() ,jobs.end() ,sort_jobs);
    int num_of_jobs = jobs.count();

    pJobs.clear();
    QString str;
    QStringList columns;
    Job_history jh;
    for(int i = 0 ;i < num_of_jobs ;i++){

        key = QString(job_key) + jobs.at(i) +"/";
        str = settings.value(key + "main").toString()
                +QString("/\\%1/\\%2/\\%3/\\%4")
                .arg(settings.value(key + "pages").toInt())
                .arg(settings.value(key + "state").toInt())
                .arg(settings.value(key + "time").toLongLong())
                .arg(settings.value(key + "job_result").toInt());
        columns = str.split("/\\");

        if(columns.length() < JobHistoryIndex_max)
            break;

        jh.id = columns.at(JobHistoryIndex_id).toInt();
        jh.result = columns.at(JobHistoryIndex_result).toInt();
        jh.copies = columns.at(JobHistoryIndex_copies).toInt();
        jh.pages = columns.at(JobHistoryIndex_pages).toInt();
        jh.state = columns.at(JobHistoryIndex_state).toInt();
        jh.time = columns.at(JobHistoryIndex_time).toLongLong();
        jh.printername = columns.at(JobHistoryIndex_printername).toUtf8();
        jh.hostname = columns.at(JobHistoryIndex_hostname).toUtf8();
        jh.username = columns.at(JobHistoryIndex_username).toUtf8();
        jh.filename = columns.at(JobHistoryIndex_filename).toUtf8();
        jh.job_result = columns.at(JobHistoryIndex_jobresult).toInt();
        pJobs << jh;
    }
    mutex.unlock();
    return 0;
}

static int get_job_history_value(const QSettings& settings ,const QString& key ,
                          Job_history& jh)
{
    QString str;
    QStringList columns;
//    Job_history jh;
    str = settings.value(key + "main").toString()
            +QString("/\\%1/\\%2/\\%3/\\%4")
            .arg(settings.value(key + "pages").toInt())
            .arg(settings.value(key + "state").toInt())
            .arg(settings.value(key + "time").toLongLong())
            .arg(settings.value(key + "job_result").toInt());
    columns = str.split("/\\");

    if(columns.length() < JobHistoryIndex_max)
        return -1;

    jh.id = columns.at(JobHistoryIndex_id).toInt();
    jh.result = columns.at(JobHistoryIndex_result).toInt();
    jh.copies = columns.at(JobHistoryIndex_copies).toInt();
    jh.pages = columns.at(JobHistoryIndex_pages).toInt();
    jh.state = columns.at(JobHistoryIndex_state).toInt();
    jh.time = columns.at(JobHistoryIndex_time).toLongLong();
    jh.printername = columns.at(JobHistoryIndex_printername);
    jh.hostname = columns.at(JobHistoryIndex_hostname);
    jh.username = columns.at(JobHistoryIndex_username);
    jh.filename = columns.at(JobHistoryIndex_filename);
    jh.job_result = columns.at(JobHistoryIndex_jobresult).toInt();
    return 0;
}

int FilterJobHistory::get_job_history(QList<Job_history >& pJobs ,int page ,int countofpage)
{
    mutex.lock();
    QSettings settings(job_history_file_name ,QSettings::defaultFormat());
    QString key(job_key);
    settings.beginGroup(key);
    QStringList jobs = settings.childGroups();
    settings.endGroup();

    if(jobs.isEmpty())
        return 0;

    qSort(jobs.begin() ,jobs.end() ,sort_jobs);
    int num_of_jobs = jobs.count();
    int pages = num_of_jobs / countofpage + 1;
    if(page > pages){
        page = pages - 1;
        LOGLOG("out of page");
        return -1;
    }
    int index = page * countofpage;

    pJobs.clear();
    int ret;
    Job_history jh;
    for(int i = 0 ;i < countofpage ;i++,index++){
        if(index > num_of_jobs - 1)
            break;
        key = QString(job_key) + jobs.at(index) +"/";
        ret = get_job_history_value(settings ,key ,jh);
        if(ret)
            break;
        pJobs << jh;
    }

    mutex.unlock();
    return 0;
}



static void callback_updatJobList(void* para,Job_struct* js)
{
    QStringList jobs = *(QStringList*)para;
    if(!jobs.contains(QString("%1").arg(js->id))){
        return;
    }
    //update job state
    mutex.lock();
    QSettings settings(job_history_file_name ,QSettings::defaultFormat());
    QString key = QString().sprintf("%s%d/" ,job_key ,js->id);
    settings.setValue(key + "pages" ,js->pages_completed);
    settings.setValue(key + "state" ,js->state);//JOBSTATE_COMPLETED?
    settings.setValue(key + "time" ,js->timet);
    settings.sync();
    mutex.unlock();
}

int FilterJobHistory::update_job_history()
{
    mutex.lock();
    QSettings settings(job_history_file_name ,QSettings::defaultFormat());
    QString key(job_key);
    settings.beginGroup(key);
    QStringList jobs = settings.childGroups();
    settings.endGroup();
    mutex.unlock();
    cups_get_job(callback_updatJobList ,(void*)&jobs);
    return 0;
}

#include "commonapi.h"
#include "smconfig.h"
extern int snmp_get_jobhistory(char* ip ,char* buffer ,int bufsize);
typedef struct{
    unsigned int ReportID;
    unsigned int uiJobResult;
    int uiJobID;
    char HostID[10];
    char DocID[31];
}
    FW_jobhistory_struct;
static int getPrinterList(void* ,Printer_struct* ps)
{
    int ret = 1;
    if(isDeviceSupported && isDeviceSupported(ps)){
        if(!QString(ps->deviceUri).startsWith("usb://")){
            QString ip = NetIO::resolve_uri(ps->deviceUri);
            if(ip.isEmpty()){
                return 1;
            }
            if(ip.startsWith("[")){//ipv6
                ip = "udp6:" + ip;
            }
            char buffer[1024];
            int size_of_job_history;
            Job_history jh;
            size_of_job_history = snmp_get_jobhistory(ip.toLatin1().data() ,buffer ,1024);
            if(size_of_job_history > 0){
                //update job result
                mutex.lock();
                QSettings settings(job_history_file_name ,QSettings::defaultFormat());
                for(int i = 0 ;i < size_of_job_history ;i += sizeof(FW_jobhistory_struct)){
                    FW_jobhistory_struct* fw = (FW_jobhistory_struct*)(buffer + i);
//                    LOGLOG("snmp get job history:%d ,%d ,%d ,%s ,%s"
//                           ,fw->ReportID ,fw->uiJobResult ,fw->uiJobID
//                           ,QString(fw->HostID).left(9).toUtf8().constData()
//                           ,QString(fw->DocID).left(31).toUtf8().constData());
                    QString key = QString().sprintf("%s%d/" ,job_key ,fw->uiJobID);
                    if(settings.contains(key + "main")){
#ifndef DEBUG_DEBUG
                        ret = get_job_history_value(settings ,key ,jh);
//                        LOGLOG("job history host name:%s" ,jh.hostname.toUtf8().constData());
                        if(!ret
                                && (jh.job_result != -2)
                                && !jh.hostname.left(9).compare(QString(fw->HostID).left(9))
                                )
#endif
                        settings.setValue(key + "job_result" ,fw->uiJobResult);
                    }
                    settings.sync();
                }
                mutex.unlock();
            }
        }
    }
    return 1;
}

int FilterJobHistory::update_fw_job_history()
{
    cups_get_printers(getPrinterList ,NULL);
    return 0;
}
