#include "userservice.h"
#include "client.h"
#include "criticaldb.h"

#include <QSqlQuery>
#include <QSqlError>

UserService::UserService() {}

void UserService::addClient(Client &client) {
    QSqlQuery query;
    query.prepare("INSERT INTO Client (phone, name, surname, patronymic, hash_password) VALUES (?, ?, ?, ?, ?);");
    query.bindValue(0, client.getPhone());
    query.bindValue(1, client.getName());
    query.bindValue(2, client.getSurname());
    query.bindValue(3, client.getPatronymic());
    query.bindValue(4, client.getHashPassword());
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
}

// Client UserService::getClientByPhone(const QString &phone) {
//     QSqlQuery query;
//     query.prepare("SELECT * FROM Client WHERE phone = ?;");
//     query.bindValue(0, phone);
// }

bool UserService::checkUserExistsByPhone(const QString &phone) { // ?
    QSqlQuery query;
    query.prepare("SELECT phone FROM Client WHERE phone = ?;");
    query.bindValue(0, phone);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
    if (query.first()) {
        return true;
    }
    query.prepare("SELECT phone FROM Employee WHERE phone = ?;");
    query.bindValue(0, phone);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
    if (query.first()) {
        return true;
    }
    return false;
}


