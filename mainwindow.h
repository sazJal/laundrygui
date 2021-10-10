#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPalette>
#include <bluetoothuart.h>
#include <QListWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <user.h>
#include <locker.h>
#include <admin.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool isCapsLocked   = true;
    QString name_str, address_str, phone_str;
    int name_idx        = 1;
    int address_idx     = 1;
    int phone_idx       = 1;
    unsigned char crcResult;
    unsigned char data[6];
    QByteArray msg_bytes;

private:
    Ui::MainWindow *ui;
    bluetoothuart *bt; // = new bluetoothuart();
    QSerialPort *serialPort;
    user *entity;// = new user();
    admin *laundryAdmin;// = new admin(bt);
    bool connectSuccess = false;
    bool NameIsChecked  = false;
    bool AddrIsChecked  = false;
    bool PhoneIsChecked = false;

private slots:
    void open_admin();
    void open_register();
    void capitalize_all();
    void on_keyboard_clicked();
    void evaluate_radio_option();
    void clear_param(void);

};

#endif // MAINWINDOW_H
