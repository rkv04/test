#ifndef USER_H
#define USER_H

#include <QString>

class User {
public:
    User();

    enum Roles {
        Client = 0,
        Employee = 1,
        Admin = 2
    };

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
