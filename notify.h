#ifndef NOTIFY_H
#define NOTIFY_H

#include <QDialog>
#include <user.h>
#include <bluetoothuart.h>
#include <QDebug>
#include <QTimer>
#include <QtSerialPort>
#include <QMessageBox>

namespace Ui {
class notify;
}

class notify : public QDialog
{
    Q_OBJECT

public:
    explicit notify(user *User, bluetoothuart *btAdapter, QSerialPort *port, QWidget *parent = nullptr);
    ~notify();
    QByteArray msg_bytes;

private:
    Ui::notify *ui;
    user *NotifUserEntity;
    bluetoothuart *bt;// = new bluetoothuart();
    QSerialPort *serialPort;
    char recvState;
    bool isFinished;

private slots:
    void show_entry(void);
    void close_dialog(void);
    void bt_send_message(void);
    void bt_read_message(void);
    void open_lock(void);
    unsigned char CRC8(const unsigned char *data, int length);
};

#endif // NOTIFY_H
