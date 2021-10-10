#ifndef BLUETOOTHUART_H
#define BLUETOOTHUART_H

#include <QObject>
#include <QtBluetooth/qtbluetoothglobal.h>
#include <qbluetoothlocaldevice.h>
#include <qbluetoothsocket.h>
#include <qbluetoothservicediscoveryagent.h>
#include <QByteArray>
#include <qdebug.h>

#define BUFFER_SIZE 128

QT_FORWARD_DECLARE_CLASS(QBluetoothServiceDiscoveryAgent)
QT_FORWARD_DECLARE_CLASS(QBluetoothLocalDevice)

class bluetoothuart : public QObject
{
    Q_OBJECT

public:
    explicit bluetoothuart(QObject *parent = nullptr);

    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothLocalDevice *localDevice;
    QBluetoothSocket *socket;

signals:
    void emit_refresh();
    void emit_scan();

public slots:
        void bt_scan();
};

#endif // BLUETOOTHUART_H
