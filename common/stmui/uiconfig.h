#ifndef UICONFIG_H
#define UICONFIG_H

#include "pro_config.h"

//#define SERVER_PATH SERVICE_TRANS_PATH

#define LOCKER_EXE LOCKER_UI

#define EXE_NAME EXE_UI_NAME

//#define FILTERUIEXE_DIR APP_PATH

#define LOG_FILE_NAME LOG_UI_FILE

#include "statusmonitor.h"
#include <QObject>
#include <QMetaType>

extern const QString app_name;
extern bool use_status_thread;
extern bool testmode;

Q_DECLARE_METATYPE(Printer_struct)
Q_DECLARE_METATYPE(QList<Printer_struct>)
Q_DECLARE_METATYPE(PrinterInfo_struct)
Q_DECLARE_METATYPE(QList<PrinterInfo_struct>)
Q_DECLARE_METATYPE(PrinterStatus_struct)

#include "smconfig.h"
class UIConfig : public QObject ,SMConfig{
    Q_OBJECT
public:
    explicit UIConfig(QObject *parent = 0);

    static int initConfig();
    static void exit_app();
public:
    enum CmdType{
        CMD_GetDefaultPrinter,
        CMD_GetPrinters,
        CMD_SetCurrentPrinter,
        CMD_GetStatus,
    };
    Q_ENUMS(CmdType)
};


#endif // UICONFIG_H
