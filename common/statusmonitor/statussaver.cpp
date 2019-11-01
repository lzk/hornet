#include "statussaver.h"
#include "statusmanager.h"
#include "devicemanager.h"
#include "status.h"
#include "commonapi.h"
#include "smconfig.h"

StatusSaverThread::StatusSaverThread(QObject *parent)
    : QThread(parent)
    , abort(false)
    ,delay_start(false)
{
}

StatusSaverThread::~StatusSaverThread()
{
    abort = true;
    while(abort)usleep(1000);
}

void StatusSaverThread::run()
{
    StatusSaver* monitor = qobject_cast<StatusSaver* >(parent());
    QList<Printer_struct> printers;
    PrinterInfo_struct printerinfo;
    int result;
//    PRINTER_STATUS status;
    DeviceIO* device;

    if(!monitor){
        return;
    }
    if(delay_start)
        sleep(6);
    forever {
        if (abort)
            break;

        monitor->mutex.lock();
        printers = monitor->current_printerlist;
        monitor->mutex.unlock();

        for(int i = 0 ;i < printers.count() ;i++) {
            if (abort){
                break;
            }
//            if(!printers[i].isConnected)
//                continue;
            device = DeviceManager::new_device(&printers[i]);
            result = -1;
            printerinfo.printer = printers[i];
            if(device){
//                result = getStatusFromDevice(device ,&printers[i] ,&status);
                result = StatusMonitor::getDeviceStatus(device ,&printerinfo);
                delete device;
            }
            printerinfo.printer.isConnected = !result;
            printerinfo.printer.status = result;
            StatusManager().savePrinterInfoToFile(printerinfo.printer.name ,&printerinfo);
            LOGLOG("update printer %s, status:0x%02x" ,printerinfo.printer.name ,printerinfo.status.PrinterStatus);
        }
        sleep(6);
    }
    StatusManager().clearFile();
    abort = false;
}

static int callback_getPrinters(void* para,Printer_struct* ps)
{
    StatusSaver* watcher = (StatusSaver*)para;
    if(isDeviceSupported && isDeviceSupported(ps)){
        watcher->add_printer(ps);
    }
    return watcher->abort ?0 :1;
}

StatusSaver::StatusSaver(QObject *parent)
    : QThread(parent)
    ,abort(false)
    ,count(0)
{
    statusThread = new StatusSaverThread(this);
}

StatusSaver::~StatusSaver()
{
    abort = true;
    if(statusThread)
        delete statusThread;
    while(abort)usleep(1000);
}

void StatusSaver::add_printer(Printer_struct* ps)
{
    printerlist << *ps;
}

void StatusSaver::run()
{
    statusThread->start();
    forever{
        if (abort){
            break;
        }
        //update printer list
        if(count % 6 == 0){
            cups_get_printers(callback_getPrinters ,this);
//            for(int i = 0 ;i < printerlist.count() ;i++) {
//                if (abort){
//                    break;
//                }
//                if(DeviceManager::get_device_connect_status(&printerlist[i])){

//                }
//            }
            mutex.lock();
            current_printerlist = printerlist;
            mutex.unlock();
            StatusManager().savePrintersToFile(printerlist);
        }
        watcher_job();
        if(60 == count++)
            count = 0;
        usleep(1000*1000);
    }
    abort = false;
}

void StatusSaver::watcher_job()
{
}
