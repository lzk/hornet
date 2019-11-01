#include "filterlib.h"
#include "jkinterface.h"
#include "filterlibconfig.h"
#include <string.h>
#include "filtermanager.h"
#include "log.h"
#ifdef __cplusplus
extern "C" {
#endif

extern const char* log_app_name;
//extern const char* app_version;
extern const char* log_file;
int filterlib(filterlib_struct* para)
{

    log_app_name = EXE_NAME;
    app_version = APP_VERSION;
    log_file = LOG_FILE_NAME;
    log_init();
    int ret = FilterManager::filtermanager_job(para);
    FilterManager::filtermanager_job_exit();
    return ret;
}

int filterlib_exit()
{
    return 0;//FilterManager::filtermanager_job_exit();
}

int filterlib_abort()
{
    return FilterManager::filtermanager_job_abort();
}

#ifdef __cplusplus
}
#endif
