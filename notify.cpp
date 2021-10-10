#include "notify.h"
#include "ui_notify.h"

notify::notify(user *User, bluetoothuart *btAdapter, QSerialPort *port, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notify)
{
    ui->setupUi(this);
    NotifUserEntity = User;
    bt = btAdapter;
    serialPort = port;

    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &notify::bt_send_message);
    timer->start(1000);
    isFinished = false;

    connect(ui->button_confirm, &QPushButton::clicked, this, &notify::close_dialog);
    connect(ui->button_back, &QPushButton::clicked, this, &notify::close_dialog);
    connect(ui->button_send, &QPushButton::clicked, this, &notify::bt_send_message);
     connect(bt->socket, SIGNAL(readyRead()), this, SLOT(bt_read_message()));

}

notify::~notify()
{
    delete ui;
}

void notify::show_entry(void)
{
    QMessageBox msgBox;

    ui->textBrowser->append(QStringLiteral("Name :")+NotifUserEntity->Name);
    ui->textBrowser->append(QStringLiteral("Alamat :")+NotifUserEntity->Address);
    ui->textBrowser->append(QStringLiteral("No. HP :")+NotifUserEntity->Phone);
    ui->textBrowser->append(QStringLiteral("No. Loker :")+ QString::number(NotifUserEntity->lock_num));
    ui->textBrowser->append(QStringLiteral("Berat :")+QString::number(NotifUserEntity->weight, 'f', 2));
    ui->textBrowser->append(QStringLiteral("Layanan :")+NotifUserEntity->Option);

    msgBox.setText("Silahkan Masukkan Pakaian, Setelah itu tekan confirm");
    msgBox.exec();
}

void notify::open_lock(void)
{

}
void notify::close_dialog(void)
{
    serialPort->write("A");
    accept();
}

void notify::bt_send_message(void)
{
    unsigned char buff[6];
    static int ct = 0;
    static int count = 0;

    if(!isFinished)
    {
        if(ct == 3)
        {
            buff[0] = 0x04;
            buff[1] = 0x02;
            buff[2] = 0x01;
            buff[3] = (unsigned char)(NotifUserEntity->lock_num);
            buff[4] = CRC8(buff, 4);
            buff[5] = 0x0B;

            for(int j=0; j< 6; j++)
            {
                msg_bytes.append(buff[j]);
            }
            bt->socket->write(msg_bytes);
            ct = 0;
        }
        else ct++;
    }
    else
    {
        if(count == 2)
        {

            count++;
            count = 0;
            show_entry();
        }
        else if ((count >= 0) && (count < 2))
        {
            buff[0] = 0x04;
            buff[1] = 0x02;
            buff[2] = 0x02;
            buff[3] = (unsigned char)(NotifUserEntity->lock_num);
            buff[4] = CRC8(buff, 4);
            buff[5] = 0x0B;
            qDebug() << "sent";
            for(int j=0; j<6; j++)
            {
                msg_bytes.append(buff[j]);
            }
            bt->socket->write(msg_bytes);
            count++;
        }
    }
}

void notify::bt_read_message(void)
{
    char buffer[60] = {0};
    unsigned char data[6];
    unsigned char crcResult;
    unsigned char crc = 0 ;
    QByteArray get = bt->socket->readAll();

    recvState = 0;
    bool isValid = false;
    QString temp;
    int length = 0;
    int count = 0;
    float buffFloat;

    for(int i=0; i<= get.length()-1; i++)
    {
        buffer[i] = get.at(i);
    }
    for(int j=0; j<= get.length()-1; j++)
    {
        switch (recvState)
        {
            case 0 : if(buffer[j]==0x05)
                     {
                        recvState   = 1;
                        data[0]     = buffer[j];
                     }
                     break;
            case 1 : length      = buffer[j];
                     data[1]     = buffer[j];
                     recvState   = 2;
                     break;
            case 2:  if(count == length-1)
                     {
                        data[count+2] = buffer[j];
                        count = 0;
                        recvState = 3;
                     }
                     else
                     {
                        data[count+2] = buffer[j];
                        count++;
                     }
                      break;
        case 3:      crc         = buffer[j];
                     recvState   = 4;
            break;
        case 4:      if(buffer[j] == 0x0A)
                        {
                            crcResult = CRC8(data, length+2);
                            if(crcResult == crc)
                                isValid = true;
                            recvState = 0;
                        }
                break;
        default: break;
        }

    }

    if(isValid)
    {
        isFinished = true;
        *((uchar*)(&buffFloat) + 3) = data[2];
        *((uchar*)(&buffFloat) + 2) = data[3];
        *((uchar*)(&buffFloat) + 1) = data[4];
        *((uchar*)(&buffFloat) + 0) = data[5];
        NotifUserEntity->weight = buffFloat;
        qDebug() << "valid";
        temp = QString::number(NotifUserEntity->weight);
        qDebug() << temp;
        if(NotifUserEntity->lock_num == 1)
        {
           serialPort->write("1");
        }
        else if(NotifUserEntity->lock_num == 2)
        {
            serialPort->write("2");
        }
    }
    else
    {
        buffFloat = 0.0;
    }


}

unsigned char notify::CRC8(const unsigned char *data, int length)
{
    unsigned char crc = 0x00;
    unsigned char extract;
    unsigned char sum;
    for(int i=0; i<length; i++)
    {
        extract = *data;
        for(unsigned char tempI = 8; tempI; tempI--)
        {
            sum = (crc ^ extract) & 0x01;
            crc >>= 1;
            if(sum)
                crc ^= 0x8C;
            extract >>= 1;
        }
        data++;
    }

    return crc;
}
