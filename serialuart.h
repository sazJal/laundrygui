#ifndef SERIALUART_H
#define SERIALUART_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class serialuart : public QObject
{
    Q_OBJECT
public:
    explicit serialuart(QObject *parent = nullptr);

    QSerialPortInfo *portInfo;
    QSerialPort     *serial;

signals:
    void emit port_discovered(QSerialPortInfo *info);

public slots:
    void port_scan(void);
};

#endif // SERIALUART_H
