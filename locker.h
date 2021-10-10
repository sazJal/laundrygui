#ifndef LOCKER_H
#define LOCKER_H

#include <QDialog>
#include <notify.h>
#include <bluetoothuart.h>
#include <QSerialPort>
#include <user.h>

namespace Ui {
class locker;
}

class locker : public QDialog
{
    Q_OBJECT

public:
    explicit locker(user *User, bluetoothuart *btAdapter, QSerialPort *port, QWidget *parent = nullptr);
    ~locker();

private:
    Ui::locker *ui;
//    user *userEntity    = new user();
//    bluetoothuart *bt   = new bluetoothuart();
    user *userEntity;
    bluetoothuart *bt;
    QSerialPort *serialPort;

private slots:
    void on_locker_selected(void);

};

#endif // LOCKER_H
