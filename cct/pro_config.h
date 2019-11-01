#ifndef PRO_CONFIG_H
#define PRO_CONFIG_H

#define APP_VERSION "1.0.8"

#define APP_PATH "/usr/share/hxpl3z/"

#define EXE_SERVICE_NAME "hxpl3zservice"
#define EXE_TRANS_NAME "hxpl3zsm"
#define EXE_UI_NAME "hxpl3zsmui"
#define EXE_FILTERUI_NAME "hxpl3zfilterui"
#define EXE_FILTERLIB_NAME "hxpl3zfilterlib"

#ifdef DEBUG_DEBUG
#define LOG_TRANS_FILE "/tmp/hxpl3zsm.log"
#define LOG_SERVICE_FILE "/tmp/hxpl3zservice.log"
#define LOG_UI_FILE "/tmp/hxpl3zsmui.log"
#define LOG_FILTERUI_FILE "/tmp/hxpl3zfilterui.log"
#define LOG_FILTERLIB_FILE "/tmp/hxpl3zfilterlib.log"
#else
#define LOG_TRANS_FILE "/usr/share/hxpl3z/sm.log"
#define LOG_SERVICE_FILE "/usr/share/hxpl3z/service.log"
#define LOG_UI_FILE "/usr/share/hxpl3z/ui.log"
#define LOG_FILTERUI_FILE "/usr/share/hxpl3z/filterui.log"
#define LOG_FILTERLIB_FILE "/var/spool/cups/tmp/hxpl3zfilterlib.log"
#endif


#define FILTER_TRANS_PATH "/var/spool/cups/tmp/hxpl3ztransrw"
#define SERVICE_TRANS_PATH "/tmp/hxpl3ztransrw"
//#define SERVER_PATH "/usr/share/hxpl3z/transrw"

#define LOCKER_SERVICE "/tmp/.hxpl3zservice_locker"
#define LOCKER_TRANS "/tmp/.hxpl3zsm_locker"
#define LOCKER_UI "/tmp/.hxpl3zsmui_locker"

#define DOMAIN_UIEXE "/tmp/hxpl3zsmui.domain"

#define STATUS_FILE "/tmp/.hxpl3zstatus"
#define STATUS_LOCKER_FILE "/tmp/.hxpl3zstatus_lock"
#define TEST_STATUS_FILE "/tmp/.status"
#define TEST_STATUS_LOCKER_FILE "/tmp/.status_lock"

#ifdef DEBUG_DEBUG
#define CONFIG_FILE "/tmp/app.conf"
#else
#define CONFIG_FILE "/usr/share/hxpl3z/config/app.conf"
#endif
#define CONFIG_KEY_isLoginWhenPrinting "is_login_when_printing"


#ifndef DEBUG_DEBUG
#define Trans_Conf_file "/usr/share/hxpl3z/config/sm.conf"
//#define Trans_Conf_file "/tmp/.hxpl3zsm.conf"
#define JOBHISTORYFILE "/usr/share/hxpl3z/job_history.xml"
#else
#define Trans_Conf_file "/tmp/hxpl3zsm.conf"
#define JOBHISTORYFILE "/tmp/hxpl3zjob_history.xml"
#endif

#endif // PRO_CONFIG_H
