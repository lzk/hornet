#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariant>
#include "uiconfig.h"
#include <QSystemTrayIcon>
#include "about.h"

class QMenu;
class QAction;
class QDialog;
namespace Ui {
class MainWindow;
}
class QListWidgetItem;
class QCloseEvent;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
//    void closeEvent(QCloseEvent *event);// override;


private slots:
    void cmdResult(int cmd,int result ,QVariant data=QVariant());
    void about();

    void on_checkBox_clicked();

    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    void messageClicked();

    void on_listWidget_printers_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_printers_itemSelectionChanged();

private:
    Ui::MainWindow *ui;
    About* about_dialog;
    QDialog* dialog;

    QString current_printer;

    QStringList printers;
//    QList<PrinterInfo_struct> printerInfos;
    QList<Printer_struct> printerlist;

    void setcurrentPrinter(const QString& str);

    void updateToner(const PrinterStatus_struct& status);

    void updateStatus(const PrinterStatus_struct& status);

    void updateOtherStatus(const QString& printer ,const PrinterStatus_struct& status);

    void updatePrinter(const QVariant& data);


    QString get_Status_string(const PrinterStatus_struct& status);

//    QAction *minimizeAction;
//    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *aboutAction;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    void createSysTray();

    bool bCheckPrinter;
};

#endif // MAINWINDOW_H
