#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

#include <QSettings>
#ifdef DEBUG_DEBUG
#define CONFIG_FILE "/tmp/hxpl3zsm.conf"
#else
#define CONFIG_FILE "/usr/share/hxpl3z/config/app.conf"
#endif
#define CONFIG_KEY_isLoginWhenPrinting "is_login_when_printing"

static int callback_getPrinters(void* para,Printer_struct* ps)
{
    MainWindow* watcher = (MainWindow*)para;
    watcher->setPrinters(ps);
    return 1;
}

void MainWindow::setPrinters(Printer_struct* ps)
{
    printers << ps->name;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    printers.clear();
    cups_get_printers(callback_getPrinters ,this);
    ui->comboBox->addItems(printers);
    if(printers.isEmpty()){

    }

//    bool is_login_when_printing;
//    QVariant value;
//    QSettings settings(CONFIG_FILE ,QSettings::NativeFormat);
//    QString key = QString("%1/%2").arg(CONFIG_KEY_isLoginWhenPrinting).arg("test printer");
//    value = settings.value(key ,false);
//    is_login_when_printing = value.toBool();
//    ui->checkBox->setChecked(is_login_when_printing);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "filterjobhistory.h"
#include "filterlib.h"
void MainWindow::on_pushButton_clicked()
{
    QList<Job_history > jobs;
    int ret = FilterJobHistory::get_job_history(jobs ,0);

    if(ret)
        return;
    if(jobs.isEmpty())
        return;
    int base = 0;

//    ui->tableWidget_jobs->clear();
    ui->tableWidget_jobs->setRowCount(jobs.length());
    QTableWidgetItem* item;
//    item = new QTableWidgetItem(QString::fromUtf8("打印机名称"));
//    ui->tableWidget_jobs->setHorizontalHeaderItem(0, item);
//    item = new QTableWidgetItem(QString::fromUtf8("计算机名称"));
//    ui->tableWidget_jobs->setHorizontalHeaderItem(1, item);
//    item = new QTableWidgetItem(QString::fromUtf8("用户名称"));
//    ui->tableWidget_jobs->setHorizontalHeaderItem(2, item);
//    item = new QTableWidgetItem(QString::fromUtf8("文件名称"));
//    ui->tableWidget_jobs->setHorizontalHeaderItem(3, item);
//    item = new QTableWidgetItem(QString::fromUtf8("页数"));
//    ui->tableWidget_jobs->setHorizontalHeaderItem(4, item);
//    item = new QTableWidgetItem(QString::fromUtf8("份数"));
//    ui->tableWidget_jobs->setHorizontalHeaderItem(5, item);
//    item = new QTableWidgetItem(QString::fromUtf8("打印时间"));
//    ui->tableWidget_jobs->setHorizontalHeaderItem(6, item);
//    item = new QTableWidgetItem(QString::fromUtf8("是否通过指纹验证"));
//    ui->tableWidget_jobs->setHorizontalHeaderItem(7, item);
//    item = new QTableWidgetItem(QString::fromUtf8("验证结果"));
//    ui->tableWidget_jobs->setHorizontalHeaderItem(8, item);
//    item = new QTableWidgetItem(QString::fromUtf8("打印结果"));
//    ui->tableWidget_jobs->setHorizontalHeaderItem(9, item);

    base = 0;
    int result;
    QString str_is_enable;
    QString str_checked;
    QString str_cups;
    QString str_fw;
    for(int i = 0 ;i < jobs.length() ;i++){

        item = new QTableWidgetItem(tr("%1").arg(jobs[i].printername));
        ui->tableWidget_jobs->setItem(i ,base+0 ,item);
        item = new QTableWidgetItem(tr("%1").arg(jobs[i].hostname));
        ui->tableWidget_jobs->setItem(i ,base+1,item);
        item = new QTableWidgetItem(tr("%1").arg(jobs[i].username));
        ui->tableWidget_jobs->setItem(i ,base+2,item);
        item = new QTableWidgetItem(tr("%1").arg(jobs[i].filename));
        ui->tableWidget_jobs->setItem(i ,base+3,item);
        item = new QTableWidgetItem(tr("%1").arg(jobs[i].pages));
        ui->tableWidget_jobs->setItem(i ,base+4,item);
        item = new QTableWidgetItem(tr("%1").arg(jobs[i].copies));
        ui->tableWidget_jobs->setItem(i ,base+5,item);
        QDateTime datetime;
        datetime.setTime_t(jobs[i].time);
        item = new QTableWidgetItem(tr("%1").arg(datetime.toString()));
        result = jobs[i].result;
        if(result == Filterlib_Status_invalidJobid){
            str_is_enable = "-";
            str_checked = "-";
        }else{
            str_is_enable = result != Filterlib_Status_nologin_model?"是":"否";
            switch (result) {
            case Filterlib_Status_OK:
                str_checked = "是";
                break;
            case Filterlib_Status_Cancel:
                str_checked = "取消";
                break;
            case Filterlib_Status_timeout:
                str_checked = "超时";
                break;
            case Filterlib_Status_checking:
                str_checked = "正在验证";
                break;
            case Filterlib_Status_nologin_model:
            case Filterlib_Status_Fail:
            case Filterlib_Status_invalidJobid:
            case Filterlib_Status_authorize_fail:
            default:
                str_checked = "否";
                break;
            }
        }
        ui->tableWidget_jobs->setItem(i ,base+6,item);
        item = new QTableWidgetItem(tr("%1").arg(str_is_enable));
        ui->tableWidget_jobs->setItem(i ,base+7,item);
        item = new QTableWidgetItem(tr("%1").arg(str_checked));
        ui->tableWidget_jobs->setItem(i ,base+8,item);
        switch (jobs[i].state) {
        case JOBSTATE_COMPLETED:
            str_cups = "完成";
            break;
        case JOBSTATE_PENDING:
        case JOBSTATE_HELD:
        case JOBSTATE_PROCESSING:
        case JOBSTATE_STOPPED:
        case JOBSTATE_CANCELED:
        case JOBSTATE_ABORTED:
        default:
            str_cups = "未完成";
            break;
        }
        item = new QTableWidgetItem(tr("%1").arg(str_cups));
        ui->tableWidget_jobs->setItem(i ,base+9,item);
        switch (jobs[i].job_result) {
        case 0xcf://SM_IsError
        case 0xc0://SM_IsPaperJam
        case 0xca://SM_IsUserIntervene
        case 0xc1://SM_IsDoorOpen
        case 0xc5://SM_IsNoToner
        case 0xc4://SM_IsPaperProblem
        case 0xc3://SM_IsOutofPaper
        case 0xcd://SM_IsTrayDetached
            break;
        case 0://print out completed
        case 1://cancel
        case 2://print with error
        case 3:
        default:
            break;
        }
        item = new QTableWidgetItem(tr("%1").arg(jobs[i].job_result));
        ui->tableWidget_jobs->setItem(i ,base+10,item);
    }
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    QSettings settings(CONFIG_FILE ,QSettings::NativeFormat);
    QString key = QString("%1/%2").arg(CONFIG_KEY_isLoginWhenPrinting).arg(ui->comboBox->currentText());
    settings.setValue(key ,checked);
    settings.sync();
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{    bool is_login_when_printing;
     QVariant value;
     QSettings settings(CONFIG_FILE ,QSettings::NativeFormat);
     QString key = QString("%1/%2").arg(CONFIG_KEY_isLoginWhenPrinting).arg(arg1);
     value = settings.value(key ,false);
     is_login_when_printing = value.toBool();
     ui->checkBox->setChecked(is_login_when_printing);
}
