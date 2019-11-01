#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidget>
#include "uinterface.h"
#include <QDateTime>
#include <unistd.h>
#include <QDebug>
#include <QAction>
#include <QMenu>
#include <QCloseEvent>
#include <QMessageBox>
#include "statuspaser.h"
#define TEST 0
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  ,about_dialog(NULL)
  ,bCheckPrinter(true)
{
    ui->setupUi(this);
    setWindowTitle(app_name);
    ui->mainToolBar->hide();

    setFixedSize(750 ,480);

    ui->statusUpdate_groupBox->hide();

    createSysTray();

    connect(gUInterface ,SIGNAL(cmdResult(int,int,QVariant)) ,this ,SLOT(cmdResult(int,int,QVariant)));

    PrinterStatus_struct status;
    memset(&status ,-1 ,sizeof(status));
    updateToner(status);
    updateStatus(status);

//    gUInterface->setCmd(UIConfig::CMD_GetPrinters ,QString());
}

MainWindow::~MainWindow()
{
    delete ui;
    if(about_dialog){
        delete about_dialog;
    }
}

void MainWindow::about()
{
    if(!about_dialog){
        about_dialog = new About;
    }
//    if(about_dialog->isHidden())
        about_dialog->show();
        about_dialog->raise();
}

void MainWindow::createSysTray()
{

//    minimizeAction = new QAction(tr("Mi&nimize"), this);
//    connect(minimizeAction, SIGNAL(triggered(bool)), this, SLOT(hide()));
////    connect(minimizeAction, SIGNAL(triggered(bool)), this, SLOT(showMinimized()));

//    maximizeAction = new QAction(tr("Ma&ximize"), this);
//    connect(maximizeAction, SIGNAL(triggered(bool)), this, SLOT(showMaximized()));

//    restoreAction = new QAction(tr("&Restore"), this);
    restoreAction = new QAction(tr("显示(&R)"), this);
    connect(restoreAction, SIGNAL(triggered(bool)), this, SLOT(showNormal()));
    aboutAction = new QAction(tr("关于..."), this);
    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(about()));
    quitAction = new QAction(tr("退出(&Q)"), this);
    connect(quitAction, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    trayIconMenu = new QMenu(this);
//    trayIconMenu->addAction(minimizeAction);
//    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addAction(aboutAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/image/app_icon.png"));
    trayIcon->setToolTip(app_name);

    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    trayIcon->show();
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        break;
    case QSystemTrayIcon::DoubleClick:{
        if(printers.isEmpty() && !testmode){

            QMessageBox message_box;
            message_box.setButtonText(QMessageBox::Ok ,"确定");
            message_box.setIcon(QMessageBox::Critical);
            message_box.setText("系统中未安装打印机。");
            message_box.setWindowTitle(" ");
            message_box.exec();
        }else{
            showNormal();
        }
    }
        break;
    case QSystemTrayIcon::MiddleClick:
//        showMessage();
        break;
    default:
        ;
    }
}

void MainWindow::messageClicked()
{
    showNormal();
}

//void MainWindow::closeEvent(QCloseEvent *event)
//{
//#ifdef Q_OS_OSX
//    if (!event->spontaneous() || !isVisible()) {
//        return;
//    }
//#endif
//    if (trayIcon->isVisible()) {
////        QMessageBox::information(this, tr("Systray"),
////                                 tr("The program will keep running in the "
////                                    "system tray. To terminate the program, "
////                                    "choose <b>Quit</b> in the context menu "
////                                    "of the system tray entry."));
//        hide();
//        event->ignore();
//    }
//}

void MainWindow::cmdResult(int cmd,int result ,QVariant data)
{
    switch(cmd){
    case UIConfig::CMD_GetDefaultPrinter:{
        if(!result){
            QString default_printer = data.toString();
            setcurrentPrinter(default_printer);
        }

    }
        break;
    case UIConfig::CMD_GetStatus:{
        PrinterInfo_struct printerInfo = data.value<PrinterInfo_struct>();
        PrinterStatus_struct& status = printerInfo.status;
        if(!printerInfo.printer.name[0] || !current_printer.compare(printerInfo.printer.name)){
#if TEST
    status.PrinterStatus = 0;
    status.TonelStatusLevelC = 80;
    status.TonelStatusLevelM = 100;
    status.TonelStatusLevelY = 10;
    status.TonelStatusLevelK = 30;
#endif
            PrinterInfo_struct* ps = &printerInfo;
            bool update = true;
            if(!ps->printer.status){//valid status
            }else{
                if(ps->printer.status == usb_error_printing){//cannot get status
                    status.PrinterStatus =  PS_PRINTING;
                }else if(ps->printer.status == usb_error_scanning){
                    status.PrinterStatus =  PS_BUSY;
                }else if(ps->printer.status == usb_error_busy){
                    update = false;
                }else if(ps->printer.status == usb_error_usb_locked){
                    update = false;
                }else{
                    memset(&status ,-1 ,sizeof(status));
                }
            }
            if(update){
//                status.PrinterStatus =0xc3;
//                status.ErrorCodeGroup = 4;
//                status.ErrorCodeID = 11;
//                status.PaperTray = 64+2;
//                status.PaperSize = 1;
//                status.PaperType = 1;
                updateStatus(status);
                updateToner(status);
    //            updateOtherStatus(printerInfo.printer.name ,status);
            }
        }
    }
        break;

    case UIConfig::CMD_GetPrinters:{
        if(!result){
            updatePrinter(data);
        }
    }
        break;

    default:
        break;
    }
}

void MainWindow::setcurrentPrinter(const QString& str)
{
    if(!current_printer.compare(str)){
        return;
    }
    PrinterStatus_struct status;
    memset(&status ,-1 ,sizeof(status));
    updateToner(status);
    updateStatus(status);
    current_printer = str;
    gUInterface->setcurrentPrinter(str);
    if(str.count() < 17){
        setWindowTitle(app_name + " - " + str);
        trayIcon->setToolTip(app_name + " - " + str);
    }else{
        setWindowTitle(app_name + " - " + str.left(8) + "..." + str.right(8));
        trayIcon->setToolTip(app_name + " - " + str.left(8) + "..." + str.right(8));
    }
//    gUInterface->setCmd(UIConfig::CMD_GetStatus ,current_printer);
}

void MainWindow::on_checkBox_clicked()
{

    if(ui->checkBox->isChecked()){
        gUInterface->setTimer(ui->lineEdit_updateInterval->text().toInt());
    }else{
        gUInterface->setTimer();
    }
}

void MainWindow::on_listWidget_printers_itemDoubleClicked(QListWidgetItem *item)
{
    setcurrentPrinter(item->toolTip());
}

void MainWindow::updateToner(const PrinterStatus_struct& status)
{
    int c ,m ,y ,k;
    c = status.TonelStatusLevelC;
    m = status.TonelStatusLevelM;
    y = status.TonelStatusLevelY;
    k = status.TonelStatusLevelK;
    if((status.PrinterStatus == 0xca)
    &&(status.ErrorCodeGroup == 5)
    ){
        switch(status.ErrorCodeID){
        case 2:k=-1;break;
        case 3:c=-1;break;
        case 4:m=-1;break;
        case 5:y=-1;break;
        default:
            break;
        }
    }
    QString c_uri = ":/image/";
    QString m_uri = ":/image/";
    QString y_uri = ":/image/";
    QString k_uri = ":/image/";
    if(c < 0){
        c_uri += "unknown";
    }else if(c == 0){
        if((status.PrinterStatus == 0x81)
        &&(status.ErrorCodeGroup == 5)
                &&(status.ErrorCodeID == 44))
            c_uri += "c5";
        else
            c_uri += "k0";
    }else if(c < 11){
        c_uri += "c5";
    }else if(c < 21){
        c_uri += "c10";
    }else if(c < 31){
        c_uri += "c20";
    }else if(c < 41){
        c_uri += "c30";
    }else if(c < 51){
        c_uri += "c40";
    }else if(c < 61){
        c_uri += "c50";
    }else if(c < 71){
        c_uri += "c60";
    }else if(c < 81){
        c_uri += "c70";
    }else if(c < 91){
        c_uri += "c80";
    }else if(c < 101){
        c_uri += "c90";
    }else{
        c_uri += "c100";
    }
    if(m < 0){
        m_uri += "unknown";
    }else if(m == 0){
        if((status.PrinterStatus == 0x81)
        &&(status.ErrorCodeGroup == 5)
                &&(status.ErrorCodeID == 45))
            m_uri += "m5";
        else
            m_uri += "k0";
    }else if(m < 11){
        m_uri += "m5";
    }else if(m < 21){
        m_uri += "m10";
    }else if(m < 31){
        m_uri += "m20";
    }else if(m < 41){
        m_uri += "m30";
    }else if(m < 51){
        m_uri += "m40";
    }else if(m < 61){
        m_uri += "m50";
    }else if(m < 71){
        m_uri += "m60";
    }else if(m < 81){
        m_uri += "m70";
    }else if(m < 91){
        m_uri += "m80";
    }else if(m < 101){
        m_uri += "m90";
    }else{
        m_uri += "m100";
    }
    if(y < 0){
        y_uri += "unknown";
    }else if(y == 0){
        if((status.PrinterStatus == 0x81)
        &&(status.ErrorCodeGroup == 5)
                &&(status.ErrorCodeID == 46))
            y_uri += "y5";
        else
            y_uri += "k0";
    }else if(y < 11){
        y_uri += "y5";
    }else if(y < 21){
        y_uri += "y10";
    }else if(y < 31){
        y_uri += "y20";
    }else if(y < 41){
        y_uri += "y30";
    }else if(y < 51){
        y_uri += "y40";
    }else if(y < 61){
        y_uri += "y50";
    }else if(y < 71){
        y_uri += "y60";
    }else if(y < 81){
        y_uri += "y70";
    }else if(y < 91){
        y_uri += "y80";
    }else if(y < 101){
        y_uri += "y90";
    }else{
        y_uri += "y100";
    }
    if(k < 0){
        k_uri += "unknown";
    }else if(k == 0){
        if((status.PrinterStatus == 0x81)
        &&(status.ErrorCodeGroup == 5)
                &&(status.ErrorCodeID == 43))
            k_uri += "k5";
        else
            k_uri += "k0";
    }else if(k < 11){
        k_uri += "k5";
    }else if(k < 21){
        k_uri += "k10";
    }else if(k < 31){
        k_uri += "k20";
    }else if(k < 41){
        k_uri += "k30";
    }else if(k < 51){
        k_uri += "k40";
    }else if(k < 61){
        k_uri += "k50";
    }else if(k < 71){
        k_uri += "k60";
    }else if(k < 81){
        k_uri += "k70";
    }else if(k < 91){
        k_uri += "k80";
    }else if(k < 101){
        k_uri += "k90";
    }else{
        k_uri += "k100";
    }
    if(c < 0){
        c_uri += ".bmp";
    }else{
        c_uri += ".png";
    }
    if(m < 0){
        m_uri += ".bmp";
    }else{
        m_uri += ".png";
    }
    if(y < 0){
        y_uri += ".bmp";
    }else{
        y_uri += ".png";
    }
    if(k < 0){
        k_uri += ".bmp";
    }else{
        k_uri += ".png";
    }
    ui->label_tonerC->setPixmap(QPixmap(c_uri));
    ui->label_tonerM->setPixmap(QPixmap(m_uri));
    ui->label_tonerY->setPixmap(QPixmap(y_uri));
    ui->label_tonerK->setPixmap(QPixmap(k_uri));
}

QString MainWindow::get_Status_string(const PrinterStatus_struct& status)
{
    QString str_status;
    ErrorInfo_struct ei = getErrorInfo(status.ErrorCodeGroup ,status.ErrorCodeID ,status.PaperType
                                       ,status.PaperSize ,status.PaperTrayStatus);
    int ps = status.PrinterStatus;
    if(ps != 0xd0){

        if ((IsStatusError(ps) && !IsStatusVirtual(ps) && ps != PS_ERROR_NOT_AVAILABLE && ps != PS_ERROR_NOT_SUPPORT) || ps == PS_TONER_LOW) {
            if(!ei.error || !ei.errorString){
                return IDS_STRUnknow;
            }
            str_status = QString() + ei.errorString->title + "(" + ei.error->code + ")";
            return str_status;
        }
    }

    switch (ps) {
    case 0://Ready
        if(status.ErrorCodeGroup == 0x05 && ((status.ErrorCodeID == 43) || (status.ErrorCodeID == 66) || (status.ErrorCodeID == 70))){
            if(!ei.error || !ei.errorString){
                str_status = IDS_STRUnknow;
            }else{
                str_status = QString() + ei.errorString->title + "(" + ei.error->code + ")";
            }
        }else{
            if(current_printer.isEmpty())
                str_status = IDS_STRUnknow;
            else
                str_status = IDS_STATUSReady;
        }
        break;
    case 1://Printing
        str_status = IDS_STATUSPrinting;
        break;
    case 2://Power Saving
        str_status = IDS_STATUSPowerSaving;
        break;
    case 3://Warmming Up
        str_status = IDS_STATUSWarningUp;
        break;
    case 4://Pending Deletion
        str_status = IDS_STRPendingDeletion;
        break;
    case 5://Paused
        str_status = IDS_STATUSPaused;
        break;
    case 6://Waiting
        str_status = IDS_STATUSWaiting;
        break;
    case 7://Processing
        str_status = IDS_STRProcessing;
        break;
    case 8://Busy
        str_status = IDS_STATUSBusy;
        break;
    case 0x80://Offline
        str_status = IDS_STATUSOffline;
        break;
    case 0x81://Toner low
        str_status = IDS_STATUSTonerLow;
        break;
    case 0x82://Initializing
        str_status = IDS_STATUSInitializing;
        break;
    case PS_MANUAL_FEED_REQUIRED:
        str_status = IDS_STATUSManualFeedRequired;
        break;
    case 0xc3: //Out of paper
        str_status = IDS_STATUSOutOfPaper;
        break;
    case 0xc5: //No toner
        str_status = IDS_STATUSNoToner;
        break;
    case 0xc1: //Door open
    case PS_ERROR_ADF_COVER_OPEN:
        str_status = IDS_STATUSDoorOpen;
        break;
    case 0xc7: //Not available
        str_status = IDS_STATUSNotAV;
        break;
    case 0xc4: //Paper problem
        str_status = IDS_STATUSPaperProblem;
        break;
    case 0xc6: //Page error
        str_status = IDS_STATUSPageError;
        break;
    case 0xc0: //Paper Jam
    case PS_ERROR_ADF_PAPER_JAM:
        str_status = IDS_STATUSPaperJam;
        break;
    case 0xc2: //Out of memory
        str_status = IDS_STATUSOutOfM;
        break;
    case 0xC9: //Not Supported
        str_status = IDS_STRUnknow;
//        str_status = IDS_STATUSNotSupported;
        break;
    case 0xca: //User intervention required
        str_status = IDS_STATUSUserIR;
        break;
    case 0xCF: //Error
        str_status = IDS_STATUSError;
        break;
    case 0xCE: //Power Off
        str_status = IDS_STRPOWEROFF;
        break;

    case 0xD0:
        str_status = "固件下载中";
        break;
    case PS_UNKNOWN:
    default:
        str_status = IDS_STRUnknow;
        break;
    }
   return str_status;
}

#include <QMovie>
void MainWindow::updateStatus(const PrinterStatus_struct& status)
{
    QString text;
    int i;
//    QString toner_text;

    int currStatus = status.PrinterStatus;
#if 0
    bool bShowLowTonerAlert = !!status.LowTonerAlert; // BMS#51330
    if (bShowLowTonerAlert && !IsStatusUnknownToner(currStatus) && StatusPaser::AnyTonerReachLevel1(status) && !StatusPaser::IsNonDellTonerMode(status)) {
        if (StatusPaser::OnlyColorTonerEmpty(status)) {
            if (IsStatusPrinting(currStatus))
                toner_text = IDS_TONER_NEED_REPLACE;
            else
                toner_text = QString();
        }
        else {
            toner_text = IDS_TONER_IS_GETTING_LOW;
        }
    }
    else {
        toner_text = QString();
    }
#endif
//    if(status.TonelStatusLevelC <20 || status.TonelStatusLevelK <20 || status.TonelStatusLevelM <20 || status.TonelStatusLevelY <20)
//    {
//        toner_text = "请更换碳粉盒。";
//        ui->label_toner->setPixmap(QPixmap(":/image/toner.png"));
//        ui->textEdit_toner->setText(toner_text);
//        ui->textEdit_toner->show();
//        ui->label_toner->show();
//    }
//    else
//    {
//        ui->label_toner->hide();
//        ui->textEdit_toner->hide();
//    }

    const PrinterStatus_struct *ps = &status;
    //update toner picture
    QString toner_pic = ":/image/";
    QString icon_status;
    if(currStatus == PS_ERROR_DOOR_OPEN){
        toner_pic += "OpenCover.gif";
        QMovie* movie = new QMovie(toner_pic);
        ui->label_printer->setMovie(movie);
        movie->start();
    }else{

        switch (currStatus) {
        case PS_ERROR_TRAY_DETACHED:
            toner_pic += "NoCassete";
            break;
        case PS_ERROR_DOOR_OPEN:
            break;
        case PS_ERROR_OUT_OF_PAPER:
            toner_pic += "Load_Paper";
            break;
        case PS_ERROR_PAPER_PROBLEM:
            toner_pic += "Load_Paper";
            break;
        case PS_ERROR_PAPER_JAM:
            if (ps->ErrorCodeGroup == 5 && ps->ErrorCodeID == 15) // Jam at input tray
                toner_pic += "MisfeedJAM";
            else
                toner_pic += "Rear_PaperJam";
            break;
        case PS_ERROR_ERROR:
            toner_pic += "PrinterError";
            break;

            //	case PS_ERROR_ADF_COVER_OPEN:
            //DrawTransparentBmps(hDC, 1, bmpID_adfcoveropen, rect, offset_adfcoveropen, RGB(255,0,255));
            //		DrawBmpList(hDC,adfOpen,rect, RGB(255,0,255));
            //		break;
            //	case PS_ERROR_ADF_PAPER_JAM:
            //DrawTransparentBmps(hDC, 1, bmpID_adfpaperjam, rect, offset_adfpaperjam, RGB(255,0,255));
            //		DrawBmpList(hDC,adfJam,rect, RGB(255,0,255));
            //		break;
        case PS_ERROR_PAGE_ERROR:
        case PS_ERROR_POWER_OFF:
        case PS_OFFLINE:
        case PS_ERROR_OUT_OF_MEMORY:
        case PS_ERROR_NOT_AVAILABLE:
        case PS_ERROR_NOT_SUPPORT:
        case PS_ERROR_OUTPUT_BIN_FULL:
        case PS_UNKNOWN:
            toner_pic += "PrinterError";
            break;
        case PS_POWER_SAVING:
        case PS_WARMING_UP:
        case PS_PRINTING:
        case PS_PENDING_DELETION:
        case PS_WAITING:
        case PS_INITIALIZING:
        case PS_BUSY:
            toner_pic += "printer";
            break;
        case PS_TONER_LOW:
        case PS_ERROR_NO_TONER:
            toner_pic += "toner";
            break;
        case PS_ERROR_USER_INTERVENTION_REQUIRED:
            if (ps->ErrorCodeGroup == 5 && (ps->ErrorCodeID >= 2 && ps->ErrorCodeID <= 9)) {	// Toner not installed
                toner_pic += "toner";
            }
            else if (ps->ErrorCodeGroup == 5 && (ps->ErrorCodeID >= 57 && ps->ErrorCodeID <= 60)) { // Unsupported Toner detected
                toner_pic += "toner";
            }
//            else if (ps->ErrorCodeGroup == 4 && ps->ErrorCodeID == 3) { // 04-003
//                toner_pic += "printer";
//            }
            else { // Maybe there are some other cases (TBD)
                   //DrawTransparentBmps(hDC, 2, bmpID_error, rect, offset_error, RGB(255,0,255));
                toner_pic += "printer";
                icon_status = ":/image/status_error.png";
            }

            break;
        case -1:
            toner_pic += "PrinterError";
            break;
        default:
            toner_pic += "printer";
            break;
        }
        toner_pic += ".png";
        ui->label_printer->setPixmap(QPixmap(toner_pic));
        ui->icon_status->setPixmap(QPixmap(icon_status));
    }

    int warning_status = 0;
    QString status_icon = ":/image/";
    if(IsStatusError(currStatus)){
        if((currStatus == PS_ERROR_TRAY_DETACHED &&  status.ErrorCodeGroup == 0x05 && status.ErrorCodeID == 72)
                ||(currStatus == PS_ERROR_OUT_OF_PAPER &&  status.ErrorCodeGroup == 0x05 && status.ErrorCodeID == 73))
            warning_status = 1;
        else
          warning_status = 2;
//    }else if(IsStatusAbnormal(currStatus) || (currStatus == PS_READY &&  status.ErrorCodeGroup == 0x05 && (status.ErrorCodeID == 72 || status.ErrorCodeID == 73 )))
    }else if(IsStatusAbnormal(currStatus)){
        warning_status = 1;
//        if(currStatus == PS_TONER_LOW)
//            warning_status = 1;
    }
    switch (warning_status) {
    case 1:
        trayIcon->setIcon(QIcon(":/image/TrayWarnning.png"));
        status_icon += "status_warning";
        break;
    case 2:
        trayIcon->setIcon(QIcon(":/image/TrayError.png"));
        status_icon += "status_error";
        break;
    case 0:
    default:
        trayIcon->setIcon(QIcon(":/image/TrayReady.png"));
        status_icon += "status_normal";
        break;
    }
    status_icon += ".png";

    bool showDetail;
//    const PrinterStatus_struct *ps = &status;
//    if (IsStatusVirtual(ps->PrinterStatus) || IsStatusTrans(ps->PrinterStatus) || ps->ErrorCodeGroup == 0 || ps->ErrorCodeID == 0 || ps->PrinterStatus == PS_ERROR_NOT_SUPPORT) {
//        showDetail = false;
//    }
//    else {
//        if (IsStatusNormal(ps->PrinterStatus))
//            showDetail = false;
//        else {
//            // Status is abnormal , then check if there are LTC code from FW
//            if (ps->ErrorCodeGroup == 0 || ps->ErrorCodeID == 0)
//                showDetail = false;
//            else {
//                showDetail = true;
//            }
//        }
//    }

    switch (currStatus) {//some status do not show detail but maybe has error info
    case 0xd0:
    case PS_PRINTING:
    case PS_BUSY:
    case PS_ERROR_NOT_SUPPORT:
    case PS_ERROR_POWER_OFF:
    case PS_PAUSED:
    case PS_OFFLINE:
    case PS_UNKNOWN:
    case PS_POWER_SAVING:
    case PS_PENDING_DELETION:
    case PS_WAITING:
    case PS_INITIALIZING:
    case PS_ACTIVE:
        showDetail = false;
        break;
    default:
        if(IsStatusNormal(currStatus) || !status.ErrorCodeGroup || !status.ErrorCodeID){
            showDetail = false;
        }else{
            showDetail = true;
        }
        break;
    }

    text = "<html><head/><body>";
    if(!showDetail){
        text += QString() + "<p>" + get_Status_string(status) + "</p>";
//        text += QString() + "<p><img src=\":/image/status_normal.png\"/>&nbsp;&nbsp;&nbsp;&nbsp;" + get_Status_string(status) + "</p>";
    }else{
        LOGLOG("paper tray:%d" ,status.PaperTrayStatus);
        ErrorInfo_struct ei = getErrorInfo(status.ErrorCodeGroup ,status.ErrorCodeID ,status.PaperType
                                           ,status.PaperSize ,status.PaperTrayStatus);
        if(!ei.error || !ei.errorString){
            text += QString() + "<p>" + get_Status_string(status) + "</p>";
//            text += QString() + "<p><img src=\":/image/status_normal.png\"/>&nbsp;&nbsp;&nbsp;&nbsp;" + get_Status_string(status) + "</p>";
            goto CODE_ERROR;
        }

        text += QString() + "<p>" + ei.errorString->title + "</p>";
//        text += QString() + "<p><img src=\":/image/status_normal.png\"/>&nbsp;&nbsp;&nbsp;&nbsp;" + ei.errorString->title + "</p>";
//        text += "<br/>";
        text += QString() + "<p>" + ei.error->code + "</p>";

        const char* extra_string = "";
        for(i = 0 ;i < ei.errorString->lines ;i++){
            extra_string = "";
//            text += "<br/>";
            if((ei.errorString->mediaInfo & 1) == 1){
                if(i == ei.errorString->lines -2)
                    extra_string = ei.paperSizeString;
                else if(i == ei.errorString->lines - 1)
                    extra_string = ei.paperTypeString;
            }
            if((ei.errorString->mediaInfo & 2) == 2){
                if(i == 0){
                    extra_string = ei.paperTrayString;
                }
            }
            switch (i)
            {
            case 0:
                text += QString() + "<p>" + ei.errorString->line0 + extra_string + "</p>";
                break;
            case 1:
                text += QString() + "<p>" + ei.errorString->line1 + extra_string + "</p>";
                break;
            case 2:
                text += QString() + "<p>" + ei.errorString->line2 + extra_string + "</p>";
                break;
            case 3:
                text += QString() + "<p>" + ei.errorString->line3 + extra_string + "</p>";
                break;
            case 4:
                text += QString() + "<p>" + ei.errorString->line4 + extra_string + "</p>";
                break;
            default:
                break;
            }
        }
    }
    CODE_ERROR:
    text += "</body></html>";
    ui->label_status->setText(text);
    if(IsStatusError(currStatus)){
        show();
    }
}

void MainWindow::updatePrinter(const QVariant& data)
{
    printerlist = data.value<QList<Printer_struct> >();
    Printer_struct printer;

    printers.clear();
    ui->listWidget_printers->clear();
    int index_of_online_printer = -1;
    int index_of_defaultprinter = 0;
    for(int i = 0 ;i < printerlist.length() ;i++){
        printer = printerlist.at(i);
        printers << printer.name;

        if(printer.isConnected){
            if(index_of_online_printer < 0)
                index_of_online_printer = i;
        }
        if(printer.isDefault){
            index_of_defaultprinter =  i;
        }
        QListWidgetItem *item;
        QString str(printer.name);
        if(str.count() < 17){
            item = new QListWidgetItem(printer.name);
            item->setToolTip(printer.name);
        }else{
            item = new QListWidgetItem(str.left(8) + "..." + str.right(8));
            item->setToolTip(printer.name);
        }
        ui->listWidget_printers->addItem(item);
//        ui->listWidget_printers->addItem(item);
    }

    if(printers.isEmpty())
    {

        LOGLOG("no printers");
        setcurrentPrinter(QString());
//        gUInterface->setTimer(0);
        if(bCheckPrinter && !testmode){
            hide();
            bCheckPrinter = false;
            QMessageBox message_box;
            message_box.setButtonText(QMessageBox::Ok ,"确定");
            message_box.setIcon(QMessageBox::Critical);
            message_box.setText("系统中未安装打印机。");
            message_box.setWindowTitle(" ");
            message_box.exec();
            exit(0);
        }
        return;
    }
    else if(printers.contains(current_printer))
    {
//        setcurrentPrinter(current_printer);
         bCheckPrinter = false;
        ui->listWidget_printers->setCurrentRow(printers.indexOf(current_printer));
    }else if(index_of_online_printer >= 0){
        bCheckPrinter = false;
        setcurrentPrinter(printers.at(index_of_online_printer));
        ui->listWidget_printers->setCurrentRow(index_of_online_printer);
    }else{
         bCheckPrinter = false;
          setcurrentPrinter(printers.at(index_of_defaultprinter));
          ui->listWidget_printers->setCurrentRow(index_of_defaultprinter);
    }
}

void MainWindow::updateOtherStatus(const QString&  ,const PrinterStatus_struct& )
{

}



void MainWindow::on_listWidget_printers_itemSelectionChanged()
{
    QListWidgetItem* item = ui->listWidget_printers->currentItem();
    if(item){
        setcurrentPrinter(item->toolTip());
    }else{
        setcurrentPrinter(QString());
    }

}
