#ifndef USERSERVICE_H
#define USERSERVICE_H

#include "user.h"

#include <QSqlQuery>
#include <QSharedPointer>

class UserService
{
public:
    UserService();

    enum class role {
        client,
        employee,
        admin
    };

    QSharedPointer<User> getClientByPhone(const QString &phone);
    QSharedPointer<User> getEmployeeByPhone(const QString &phone);
    void addClient(User &client);

private:


};

#endif // USERSERVICE_H
