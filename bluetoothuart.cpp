#include "bluetoothuart.h"

bluetoothuart::bluetoothuart(QObject *parent) : QObject(parent)
{
    discoveryAgent  = new QBluetoothDeviceDiscoveryAgent();
    localDevice     = new QBluetoothLocalDevice();
    socket          = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

}

void bluetoothuart::bt_scan(){
    qDebug() << tr("Adapter ID %1", "Address %1").arg(localDevice->address().toString());
    if(localDevice->hostMode() == QBluetoothLocalDevice::HostPoweredOff){
        localDevice->powerOn();
    }
    discoveryAgent->setInquiryType(QBluetoothDeviceDiscoveryAgent::GeneralUnlimitedInquiry);
    discoveryAgent->start();

    emit emit_refresh();
}
