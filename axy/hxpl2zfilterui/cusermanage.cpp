#include "cusermanage.h"
#include <QFile>
#include <QDebug>


CUserManage::CUserManage(QObject *parent) : QObject(parent)
{
    CheckUser = NULL;

}


bool CUserManage::initdll()
{
    QString sPath, sFileName;

#ifdef DEBUG_DEBUG
#ifdef Q_OS_DARWIN
    sFileName = "/tmp/libhxpl2zum.dylib";
#else
    sFileName = "/tmp/libhxpl2zum.so";
#endif
#else
    sFileName = "/usr/lib/libhxpl2zum.so";
//    sFileName = "/home/barryyang/Nezha2/build-libhxpl2zum-Desktop-Debug/libhxpl2zum.so.1.0.0";
    if(!QFile::exists(sFileName))
    {
        sFileName = "/usr/lib64/libhxpl2zum.so";
        if(!QFile::exists(sFileName))
        {
            sFileName = "/usr/lib/x86_64-linux-gnu/libhxpl2zum.so";
            if(!QFile::exists(sFileName))
            {
                sFileName = "/usr/lib/aarch64-linux-gnu/libhxpl2zum.so";
                if(!QFile::exists(sFileName))
                {
                    sFileName = "/usr/lib/i386-linux-gnu/libhxpl2zum.so";

                }
            }
        }
    }
#endif
    if(QFile::exists(sFileName))
    {
        m_hCommDll.setFileName(sFileName);
        //m_hCommDll = LoadLibraryEx(sFileName, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
        if(!m_hCommDll.load())
        {

            qDebug() << "load library failed";
            qDebug() << m_hCommDll.errorString();
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
        qDebug()<<sFileName<<" is not exist!";
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
