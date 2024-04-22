#include "client.h"

Client::Client(QString phone, QString hash_password, QString name, QString surname, QString patronymic) {
    this->phone = phone;
    this->hash_password = hash_password;
    this->name = name;
    this->surname = surname;
    this->patronymic = patronymic;
    this->current_discount = 0;
}

QString Client::getName() {
    return this->name;
}

QString Client::getSurname() {
    return this->surname;
}

QString Client::getPatronymic() {
    return this->patronymic;
}

QString Client::getPhone() {
    return this->phone;
}

QString Client::getHashPassword() {
    return this->hash_password;
}
