#include "locker.h"
#include "ui_locker.h"

locker::locker(user *User, bluetoothuart *btAdapter, QSerialPort *port, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::locker)
{
    ui->setupUi(this);
    userEntity  = User;
    bt          = btAdapter;
    serialPort  = port;

    ui->button_3->setEnabled(false);
    ui->button_4->setEnabled(false);
    ui->button_5->setEnabled(false);
    ui->button_6->setEnabled(false);
    ui->button_7->setEnabled(false);
    ui->button_8->setEnabled(false);
    connect(ui->button_1, &QPushButton::clicked, this, &locker::on_locker_selected);
    connect(ui->button_2, &QPushButton::clicked, this, &locker::on_locker_selected);
//    connect(ui->button_3, &QPushButton::clicked, this, &locker::on_locker_selected);
//    connect(ui->button_4, &QPushButton::clicked, this, &locker::on_locker_selected);
//    connect(ui->button_5, &QPushButton::clicked, this, &locker::on_locker_selected);
//    connect(ui->button_6, &QPushButton::clicked, this, &locker::on_locker_selected);
//    connect(ui->button_7, &QPushButton::clicked, this, &locker::on_locker_selected);
//    connect(ui->button_8, &QPushButton::clicked, this, &locker::on_locker_selected);
}

locker::~locker()
{
    delete ui;
}

void locker::on_locker_selected(void)
{
    QPushButton *button = (QPushButton *)(sender());
    QString num = button->text();

    userEntity->lock_num = num.toInt();

    notify *notif = new notify(userEntity, bt, serialPort);

    if(notif->exec() == QDialog::Accepted)
    {
        accept();
    }

}
