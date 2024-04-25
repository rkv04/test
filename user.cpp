#include "user.h"

#include <QString>

User::User() {
    this->id = -1;
    this->role = -1;
    this->phone = QString();
    this->password = QString();
    this->surname = QString();
    this->name = QString();
    this->patronymic = QString();
    this->address = QString();
    this->discount = 0;
    this->amount_purchase_tickets = 0;
}
