#ifndef CLIENT_H
#define CLIENT_H

#include <QString>

class Client {
public:
    Client(QString phone, QString hash_password, QString name, QString surname, QString patronymic);
    QString getPhone();
    QString getHashPassword();
    QString getName();
    QString getSurname();
    QString getPatronymic();
    QString getAddress();
    QString getCurrentDiscount();

private:
    int id;
    int role;
    QString phone;
    QString hash_password;
    QString name;
    QString surname;
    QString patronymic;
    QString address;
    QString current_discount;

};

#endif // CLIENT_H
