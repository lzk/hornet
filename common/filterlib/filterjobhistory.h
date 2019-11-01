#ifndef FILTERJOBHISTORY_H
#define FILTERJOBHISTORY_H

#include <QStringList>
#include "filterlib.h"

typedef
struct{
    int id;
    int result;
    int copies;
    int pages;
    int state;//JOBSTATE_COMPLETED?
    long long time;
    int job_result;

    QString printername;
    QString hostname;
    QString username;
    QString filename;
}
    Job_history;

class FilterJobHistory
{
public:
    FilterJobHistory();
    static int save_job_history(filterlib_struct* job);
    static int get_job_history(QList<Job_history >& jobs);
    static int get_job_history(QList<Job_history >& jobs ,int page ,int countofpage = 20);
    static int update_job_history();
    static int update_fw_job_history();
private:
};

#endif // FILTERJOBHISTORY_H#ifndef TOMCAT_H
