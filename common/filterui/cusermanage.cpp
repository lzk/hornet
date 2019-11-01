#include "cusermanage.h"
#include <QFile>
#include "log.h"


CUserManage::CUserManage(QObject *parent) : QObject(parent)
{
    CheckUser = NULL;

}


bool CUserManage::initdll()
{
    QString sPath, sFileName;

#if 0
//#ifdef DEBUG_DEBUG
#ifdef Q_OS_DARWIN
    sFileName = "/tmp/libhxpl3zum.dylib";
#else
    sFileName = "/tmp/libhxpl3zum.so";
#endif
#else
    sFileName = "/usr/lib/libhxpl3zum.so";
//    sFileName = "/home/barryyang/Nezha2/build-libhxpl3zum-Desktop-Debug/libhxpl3zum.so.1.0.0";
    if(!QFile::exists(sFileName))
    {
        sFileName = "/usr/lib64/libhxpl3zum.so";
        if(!QFile::exists(sFileName))
        {
            sFileName = "/usr/lib/x86_64-linux-gnu/libhxpl3zum.so";
            if(!QFile::exists(sFileName))
            {
                sFileName = "/usr/lib/aarch64-linux-gnu/libhxpl3zum.so";
                if(!QFile::exists(sFileName))
                {
                    sFileName = "/usr/lib/i386-linux-gnu/libhxpl3zum.so";

                }
            }
        }
    }
#endif
    LOGLOG("lib file name %s" ,sFileName.toUtf8().constData());
    if(QFile::exists(sFileName))
    {
        m_hCommDll.setFileName(sFileName);
        //m_hCommDll = LoadLibraryEx(sFileName, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
        if(!m_hCommDll.load())
        {
            LOGLOG("load library failed");
            LOGLOG(m_hCommDll.errorString().toUtf8().constData());
            return false;
        }
        else
        {
    //        AddFinger = (LPFNADDFINGER)m_hCommDll.resolve("AddFinger");
    //        IsDeviceConnect = (LPFNISDEVICECONNECT)m_hCommDll.resolve("IsDeviceConnect");
    //        GetDeviceConnect = (LPFNGETDEVICECONNECT)m_hCommDll.resolve("GetDeviceConnect");

    //        IsDeviceFingerOpen = (LPFNISDEVICEFINTEROPEN)m_hCommDll.resolve("IsDeviceFingerOpen");
    //        OpenFinger = (LPFNOPENFINGER)m_hCommDll.resolve("OpenFinger");
    //        CloseFinger = (LPFNCLOSEFINGER)m_hCommDll.resolve("CloseFinger");
    //        DeleteFinger = (LPFNDELETEPRINTER)m_hCommDll.resolve("DeleteFinger");
    //        DeleteFingers = (LPFNDELETEPRINTERS)m_hCommDll.resolve("DeleteFingers");
    //        CheckFinger = (LPFNCHECKFINGER)m_hCommDll.resolve("CheckFinger");
    //        ImportFinger = (LPFNIMPORTFINGER)m_hCommDll.resolve("ImportFinger");
    //        ExportFinger = (LPFNEXPORTFINGER)m_hCommDll.resolve("ExportFinger");
            Init = (LPFNINIT)m_hCommDll.resolve("Init");
            CheckUser = (LPFNCHECKUSER)m_hCommDll.resolve("CheckUser");

        }

    }
    else
    {
        LOGLOG("%s is not exist!" ,sFileName.toUtf8().constData());
        return false;
    }

//    if(m_hCommDll.isLoaded())
//    {
//        //FreeLibrary(m_hCommDll);
//        m_hCommDll.unload();
//    }

    // 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
    //  而不是启动应用程序的消息泵。
    return Init();
}

 bool CUserManage::isValidUser(char *username, char *password, char *printername)
 {

     return CheckUser(username,password,printername);
 }
