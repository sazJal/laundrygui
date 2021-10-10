#include "user.h"

user::user(QObject *parent) : QObject(parent)
{
    Address ="";
    Name    ="";
    Phone   ="";
    for(unsigned long long int j=0; j<sizeof (id); j++)
    {
        id[j] = 0;
    }
    Option      = "Kiloan";
    weight      = 0.0;
    lock_num    = 0;
    for(unsigned long long int j=0; j<sizeof (reg_date); j++)
    {
        reg_date[j] = 0;
    }
    for(unsigned long long int j=0; j<sizeof (reg_time); j++)
    {
        reg_time[j] = 0;
    }
}
