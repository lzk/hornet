#ifndef PRO_CONFIG_H
#define PRO_CONFIG_H

#define APP_VERSION "1.0.18"

#define APP_PATH "/usr/share/hxpl2z/"

#define EXE_SERVICE_NAME "hxpl2zservice"
#define EXE_TRANS_NAME "hxpl2zsm"
#define EXE_UI_NAME "hxpl2zsmui"
#define EXE_FILTERUI_NAME "hxpl2zfilterui"
#define EXE_FILTERLIB_NAME "hxpl2zfilterlib"

#ifdef DEBUG_DEBUG
#define LOG_TRANS_FILE "/tmp/hxpl2zsm.log"
#define LOG_SERVICE_FILE "/tmp/hxpl2zservice.log"
#define LOG_UI_FILE "/tmp/hxpl2zsmui.log"
#define LOG_FILTERUI_FILE "/tmp/hxpl2zfilterui.log"
#define LOG_FILTERLIB_FILE "/tmp/hxpl2zfilterlib.log"
#else
#define LOG_TRANS_FILE "/usr/share/hxpl2z/sm.log"
#define LOG_SERVICE_FILE "/usr/share/hxpl2z/service.log"
#define LOG_UI_FILE "/usr/share/hxpl2z/ui.log"
#define LOG_FILTERUI_FILE "/usr/share/hxpl2z/filterui.log"
#define LOG_FILTERLIB_FILE "/var/spool/cups/tmp/hxpl2zfilterlib.log"
#endif


#define FILTER_TRANS_PATH "/var/spool/cups/tmp/hxpl2ztransrw"
#define SERVICE_TRANS_PATH "/tmp/hxpl2ztransrw"
//#define SERVER_PATH "/usr/share/hxpl2z/transrw"

#define LOCKER_SERVICE "/tmp/.hxpl2zservice_locker"
#define LOCKER_TRANS "/tmp/.hxpl2zsm_locker"
#define LOCKER_UI "/tmp/.hxpl2zsmui_locker"

#define DOMAIN_UIEXE "/tmp/hxpl2zsmui.domain"

#define STATUS_FILE "/tmp/.hxpl2zstatus"
#define STATUS_LOCKER_FILE "/tmp/.hxpl2zstatus_lock"
#define TEST_STATUS_FILE "/tmp/.status"
#define TEST_STATUS_LOCKER_FILE "/tmp/.status_lock"

#ifdef DEBUG_DEBUG
#define CONFIG_FILE "/tmp/app.conf"
#else
#define CONFIG_FILE "/usr/share/hxpl2z/config/app.conf"
#endif
#define CONFIG_KEY_isLoginWhenPrinting "is_login_when_printing"


#ifndef DEBUG_DEBUG
#define Trans_Conf_file "/usr/share/hxpl2z/config/sm.conf"
//#define Trans_Conf_file "/tmp/.hxpl2zsm.conf"
#define JOBHISTORYFILE "/usr/share/hxpl2z/job_history.xml"
#else
#define Trans_Conf_file "/tmp/hxpl2zsm.conf"
#define JOBHISTORYFILE "/tmp/hxpl2zjob_history.xml"
#endif

#endif // PRO_CONFIG_H
