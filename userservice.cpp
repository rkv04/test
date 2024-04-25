#include "userservice.h"
#include "user.h"
#include "criticaldb.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSharedPointer>

UserService::UserService() {}

void UserService::addClient(const User &client) {
    QSqlQuery query;
    query.prepare("INSERT INTO Client (phone, name, surname, patronymic, hash_password) VALUES (?, ?, ?, ?, ?);");
    query.bindValue(0, client.phone);
    query.bindValue(1, client.name);
    query.bindValue(2, client.surname);
    query.bindValue(3, client.patronymic);
    query.bindValue(4, client.password);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
}

QSharedPointer<User> UserService::getClientByPhone(const QString &phone) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Client WHERE phone = ?;");
    query.bindValue(0, phone);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
    if (!query.first()) {
        return nullptr;
    }
    QSharedPointer<User> client = QSharedPointer<User>(new User());
    client->id = query.value("id").toInt();
    client->role = query.value("role").toInt();
    client->phone = query.value("phone").toString();
    client->password = query.value("hash_password").toString();
    client->surname = query.value("surname").toString();
    client->name = query.value("name").toString();
    client->patronymic = query.value("patronymic").toString();
    client->address = query.value("address").toString();
    client->discount = query.value("discount").toInt();
    client->amount_purchase_tickets = query.value("amount_of_purchased_tickets").toInt();
    return client;
}

QSharedPointer<User> UserService::getEmployeeByPhone(const QString &phone) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Employee WHERE phone = ?;");
    query.bindValue(0, phone);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
    if (!query.first()) {
        return nullptr;
    }
    QSharedPointer<User> employee = QSharedPointer<User>(new User());
    employee->id = query.value("id").toInt();
    employee->role = query.value("role").toInt();
    employee->phone = query.value("phone").toString();
    employee->password = query.value("hash_password").toString();
    employee->surname = query.value("surname").toString();
    employee->name = query.value("name").toString();
    employee->patronymic = query.value("patronymic").toString();
    return employee;
}

QSqlQuery UserService::getAllClients() {
    QSqlQuery query;
    QString text_query = "SELECT id, "
                                "surname AS 'Фамилия',"
                                "name AS 'Имя',"
                                "patronymic AS 'Отчество',"
                                "phone AS 'Телефон',"
                                "amount_of_purchased_tickets AS 'Путёвок куплено',"
                                "discount AS 'Скидка'"
                         "FROM Client;";
    if (!query.exec(text_query)) {
        throw CriticalDB(query.lastError().text());
    }
    return query;
}

void UserService::setDiscountById(const int client_id, const int discount) {
    QSqlQuery query;
    query.prepare("UPDATE Client SET discount = ? WHERE id = ?;");
    query.bindValue(0, discount);
    query.bindValue(1, client_id);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
}
