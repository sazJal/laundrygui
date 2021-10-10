#include "admin.h"
#include "ui_admin.h"

static const QLatin1String serviceUuid("00001101-0000-1000-8000-00805F9B34FB");

admin::admin(bluetoothuart *btAdapter, QSerialPort *port, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);

    bt = btAdapter;
    serialPort = port;

    if(bt->localDevice->hostMode() == QBluetoothLocalDevice::HostPoweredOff){
        ui->button_BT_close->setEnabled(false);
    }
    else
    {
        ui->button_BT_close->setEnabled(true);
    }

    if(serialPort->isOpen())
    {
         ui->button_COM_open->setEnabled(true);
    }
    else {
         ui->button_COM_open->setEnabled(false);
    }


    connect(ui->button_BT_scan, &QPushButton::clicked, this, &admin::bt_scan);
    connect(bt, &bluetoothuart::emit_refresh, this, &admin::bt_refresh);

    connect(bt->discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(bt_dev_discovered(QBluetoothDeviceInfo)));
    connect(bt->discoveryAgent, SIGNAL(finished()), this, SLOT(scan_finished()));
    connect(ui->list_BT, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(on_bt_item_activated(QListWidgetItem*)));
    connect(ui->button_BT_close, &QPushButton::clicked, this, &admin::bt_closed);

    connect(ui->button_COM_scan, &QPushButton::clicked, this, &admin::com_scan);
    connect(this, SIGNAL(emit_openlist(QSerialPortInfo*)), this, SLOT(com_dev_discovered(QSerialPortInfo*)));
    connect(ui->list_COM, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(on_com_item_activated(QListWidgetItem*)));
    connect(ui->button_COM_open, &QPushButton::clicked, this, &admin::com_send_something);
}

admin::~admin()
{
    delete ui;
}

void admin::bt_refresh(void)
{
    ui->button_BT_close->setEnabled(true);
}

void admin::bt_scan(void)
{
    ui->button_BT_scan->setEnabled(false);
    bt->bt_scan();
}

void admin::bt_dev_discovered(const QBluetoothDeviceInfo &info)
{
    QString label = QString("%1 %2").arg(info.address().toString(), info.name());
    QList<QListWidgetItem *> items = ui->list_BT->findItems(label, Qt::MatchExactly);

    if(items.empty()){
        QListWidgetItem *item = new QListWidgetItem(label);
        QBluetoothLocalDevice::Pairing pairingStatus = bt->localDevice->pairingStatus(info.address());
        if(pairingStatus == QBluetoothLocalDevice::Paired || pairingStatus == QBluetoothLocalDevice::AuthorizedPaired){
            item->setForeground(QColor(Qt::green));
        }
        else {
            item->setForeground(QColor(Qt::red));
        }

        ui->list_BT->addItem(item);
    }
    ui->button_BT_scan->setEnabled(true);
}

void admin::scan_finished(void)
{
    ui->browser_BT->setText("Bluetooth Connected");
}

void admin::on_bt_item_activated(QListWidgetItem *item)
{
    QString text = item->text();
    int index = text.indexOf(' ');
    qDebug() << "sampai sini";
    if(index == 1)
    {
        return;
    }
    QBluetoothAddress address(text.left(index));
    QString name(text.mid(index+1));
    QString temp = QString("%1").arg(address.toString());
    ui->browser_BT->append(QStringLiteral("MAC :")+temp);
    ui->browser_BT->append(QStringLiteral("Name :")+name);
    bt->socket->connectToService(address, QBluetoothUuid(serviceUuid), QIODevice::ReadWrite);
    connect(bt->socket, SIGNAL(connected()), this, SLOT(bt_connected()));
}

void admin::on_com_item_activated(QListWidgetItem *item)
{
    QString text = item->text();
    serialPort->setPortName(text);
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    serialPort->open(QIODevice::ReadWrite);
     qDebug() << "SerialPort Status: " << serialPort->isOpen();
     ui->button_COM_open->setEnabled(true);
    if(serialPort->isOpen())
    {
        ui->browser_COM->setText("Connected!");
    }
    else {
        ui->browser_COM->setText("No COM");
    }
}
void admin::bt_closed()
{
    serialPort->write("A");
    serialPort->write("A");
    accept();
}

void admin::com_send_something(void)
{
    serialPort->write("0");
    serialPort->write("0");
}

void admin::bt_connected()
{
    ui->browser_BT->append(QStringLiteral("Connection Succesful !"));
}

void admin::bt_read_message()
{
    QByteArray get = bt->socket->readAll();
    QString temp = get.toHex();
    ui->browser_BT->setText(temp);
}

void admin::com_scan()
{
    foreach(QSerialPortInfo port, QSerialPortInfo::availablePorts()){
        ui->list_COM->addItem(port.portName());
    }
}

