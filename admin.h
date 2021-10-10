#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include <bluetoothuart.h>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QListWidgetItem>
#include <QPushButton>
#include <QDebug>

namespace Ui {
class admin;
}

class admin : public QDialog
{
    Q_OBJECT

public:
    explicit admin(bluetoothuart *btAdapter, QSerialPort *port, QWidget *parent = nullptr);
    ~admin();

private:
    Ui::admin *ui;
    bluetoothuart *bt;
    QSerialPort *serialPort;

private slots:
    void bt_scan(void);
    void bt_refresh(void);
    void bt_dev_discovered(const QBluetoothDeviceInfo &info);
    void com_scan(void);
    void scan_finished(void);
    void on_bt_item_activated(QListWidgetItem *item);
    void on_com_item_activated(QListWidgetItem *item);
    void bt_closed(void);
    void bt_connected(void);
    void bt_read_message(void);
    void com_send_something(void);
};

#endif // ADMIN_H
