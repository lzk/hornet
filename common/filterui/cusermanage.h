#ifndef CUSERMANAGE_H
#define CUSERMANAGE_H

#include <QObject>
#include <QLibrary>

typedef bool (*LPFNCHECKUSER)(char *username, char *password, char *printername);
typedef bool (*LPFNINIT)();

class CUserManage : public QObject
{
    Q_OBJECT
public:
    explicit CUserManage(QObject *parent = NULL);

public:
    bool initdll();
    bool isValidUser(char *username, char *password, char *printername);
private:
    QLibrary m_hCommDll;
    LPFNCHECKUSER CheckUser;
    LPFNINIT Init;

signals:

public slots:
};

#endif // CUSERMANAGE_H
