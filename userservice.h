#ifndef USERSERVICE_H
#define USERSERVICE_H

#include "user.h"

#include <QSqlQuery>
#include <QSharedPointer>

class UserService
{
public:
    UserService();

    QSharedPointer<User> getClientByPhone(const QString &phone);
    QSqlQuery getAllClients();
    void setDiscountById(const int id_client, const int discount);
    QSharedPointer<User> getEmployeeByPhone(const QString &phone);
    void addClient(const User &client);

private:


};

#endif // USERSERVICE_H
