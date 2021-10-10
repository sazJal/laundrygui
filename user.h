#ifndef USER_H
#define USER_H

#include <QObject>

class user : public QObject
{
    Q_OBJECT
public:
    explicit user(QObject *parent = nullptr);

    char id[6];
    QString Name;
    QString Address;
    QString Phone;
    QString Option;
    float weight;
    int lock_num;
    int reg_date[3];
    int reg_time[3];

signals:

public slots:
};

#endif // USER_H
