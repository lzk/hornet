#ifndef STATUSSAVER_H
#define STATUSSAVER_H

#include <QThread>
#include "statusmonitor.h"
#include "devicemanager.h"
#include <QMutex>
#include <QStringList>
class DeviceManager;
class StatusSaverThread : public QThread
{
    Q_OBJECT
public:
    explicit StatusSaverThread(QObject *parent = NULL);
    ~StatusSaverThread();

    void run();

private:
    bool abort;
    bool delay_start;

    friend class StatusSaver;
};

class StatusSaver : public QThread
{
    Q_OBJECT
public:
    explicit StatusSaver(QObject *parent = 0);
    ~StatusSaver();
    void run();

    void add_printer(Printer_struct*);

    bool abort;
protected:
    virtual void watcher_job();

protected:
    QMutex mutex;
    int count;

private:
    StatusSaverThread* statusThread;

    QList<Printer_struct> printerlist;
//    QList<PrinterInfo_struct> printerinfo_list;

    QList<Printer_struct> current_printerlist;
//    QList<PrinterInfo_struct> current_printerinfo_list;

    friend class StatusSaverThread;
};

#endif // STATUSSAVER_H
