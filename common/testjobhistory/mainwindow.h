#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "jkinterface.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setPrinters(Printer_struct* ps);
private slots:
    void on_pushButton_clicked();

    void on_checkBox_toggled(bool checked);

    void on_comboBox_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;

    QStringList printers;
};

#endif // MAINWINDOW_H
