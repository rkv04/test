#ifndef USER_H
#define USER_H

#include <QString>

class User {
public:
    User();

    int id;
    int role;
    QString phone;
    QString password;
    QString name;
    QString surname;
    QString patronymic;
    QString address;
    int discount;
    int amount_purchase_tickets;
};

#endif // USER_H
