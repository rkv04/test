#ifndef USERSERVICE_H
#define USERSERVICE_H

#include "client.h"

#include <QSqlQuery>

class UserService
{
public:
    UserService();

    enum class role {
        client,
        employee,
        admin
    };

    Client getClientByPhone(const QString &phone);
    QSqlQuery getClientsByFilter();
    void addClient(Client &client);
    void removeClientByID(); // or phone
    bool checkClientExistsByPhone(const QString &phone);

private:


};

#endif // USERSERVICE_H
