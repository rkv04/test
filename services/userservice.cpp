#include "userservice.h"
#include "user.h"
#include "criticaldb.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVector>
#include <QSqlError>
#include <QSharedPointer>

UserService::UserService() {}

void UserService::addClient(const QSharedPointer<User> &client) {
    QSqlQuery query;
    query.prepare("INSERT INTO Client (phone, name, surname, patronymic, hash_password) VALUES (?, ?, ?, ?, ?);");
    query.bindValue(0, client->phone);
    query.bindValue(1, client->name);
    query.bindValue(2, client->surname);
    query.bindValue(3, client->patronymic);
    query.bindValue(4, client->password);
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
    auto client = this->createClientByRow(query.record());
    return client;
}

int UserService::addEmployee(const QSharedPointer<User> &employee) {
    QSqlQuery query;
    query.prepare("INSERT INTO Employee (surname, name, patronymic, phone, hash_password) VALUES (?, ?, ?, ?, ?);");
    query.bindValue(0, employee->surname);
    query.bindValue(1, employee->name);
    query.bindValue(2, employee->patronymic);
    query.bindValue(3, employee->phone);
    query.bindValue(4, employee->password);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
    return this->getIdLastAddedEmployee();
}

int UserService::getIdLastAddedEmployee() {
    QSqlQuery query;
    QString text_query = "SELECT id FROM Employee ORDER BY id DESC LIMIT 1";
    if (!query.exec(text_query)) {
        throw CriticalDB(query.lastError().text());
    }
    query.first();
    return query.value("id").toInt();
}

QSharedPointer<User> UserService::getEmployeeByPhone(const QString &phone) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Employee WHERE phone = ? AND activity_flag = 1;");
    query.bindValue(0, phone);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
    if (!query.first()) {
        return nullptr;
    }
    auto employee = this->createEmployeeByRow(query.record());
    return employee;
}

QVector<QSharedPointer<User>> UserService::getEmployeeList() {
    QSqlQuery query;
    QString text_query = "SELECT * FROM Employee WHERE activity_flag = 1;";
    if (!query.exec(text_query)) {
        throw CriticalDB(query.lastError().text());
    }
    return this->getEmployeeListByQuery(query);
}

QVector<QSharedPointer<User>> UserService::getEmployeeListByFilter(const QMap<QString, QString> &filter) {
    QSqlQuery query;
    QString text_query = "SELECT * FROM Employee "
                         "WHERE activity_flag = 1 AND (surname LIKE ?) AND (name LIKE ?) "
                         "AND (patronymic LIKE ?) AND (phone LIKE ?)";
    query.prepare(text_query);
    query.bindValue(0, filter["surname"]);
    query.bindValue(1, filter["name"]);
    query.bindValue(2, filter["patronymic"]);
    query.bindValue(3, filter["phone"]);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
    return this->getEmployeeListByQuery(query);
}

QVector<QSharedPointer<User>> UserService::getEmployeeListByQuery(QSqlQuery &query) {
    QVector<QSharedPointer<User>> employees;
    while (query.next()) {
        auto employee = this->createEmployeeByRow(query.record());
        employees.append(employee);
    }
    return employees;
}

QVector<QSharedPointer<User>> UserService::getClientList() {
    QSqlQuery query;
    QString text_query = "SELECT * FROM Client;";
    if (!query.exec(text_query)) {
        throw CriticalDB(query.lastError().text());
    }
    return this->getClientListByQuery(query);
}

QVector<QSharedPointer<User>> UserService::getClientsByFilter(const QMap<QString, QString> &filter) {
    QSqlQuery query;
    query.prepare("SELECT * "
                    "FROM Client "
                    "WHERE (surname LIKE :s) AND (name LIKE :n) "
                        "AND (patronymic LIKE :pt) AND (phone LIKE :ph);");
    query.bindValue(":s", filter["surname"] + "%");
    query.bindValue(":n", filter["name"] + "%");
    query.bindValue(":pt", filter["patronymic"] + "%");
    query.bindValue(":ph", filter["phone"] + "%");
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
    return this->getClientListByQuery(query);
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

void UserService::increaseAmountOfPurchaseTicketsById(const int id, const int quantity) {
    QSqlQuery query;
    query.prepare("UPDATE Client SET amount_of_purchased_tickets = amount_of_purchased_tickets + ? WHERE id = ?");
    query.bindValue(0, quantity);
    query.bindValue(1, id);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
}

QSharedPointer<User> UserService::createClientByRow(const QSqlRecord &record) {
    auto client = QSharedPointer<User>(new User());
    client->id = record.value("id").toInt();
    client->role = record.value("role").toInt();
    client->phone = record.value("phone").toString();
    client->password = record.value("hash_password").toString();
    client->surname = record.value("surname").toString();
    client->name = record.value("name").toString();
    client->patronymic = record.value("patronymic").toString();
    client->address = record.value("address").toString();
    client->discount = record.value("discount").toInt();
    client->amount_purchase_tickets = record.value("amount_of_purchased_tickets").toInt();
    return client;
}

QSharedPointer<User> UserService::createEmployeeByRow(const QSqlRecord &record) {
    auto employee = QSharedPointer<User>(new User());
    employee->id = record.value("id").toInt();
    employee->role = record.value("role").toInt();
    employee->phone = record.value("phone").toString();
    employee->password = record.value("hash_password").toString();
    employee->surname = record.value("surname").toString();
    employee->name = record.value("name").toString();
    employee->patronymic = record.value("patronymic").toString();
    return employee;
}

QVector<QSharedPointer<User>> UserService::getClientListByQuery(QSqlQuery &query) {
    QVector<QSharedPointer<User>> users;
    while (query.next()) {
        auto user = this->createClientByRow(query.record());
        users.append(user);
    }
    return users;
}

void UserService::updateUserPassword(const QSharedPointer<User> &user, const QString &hash_password)  {
    QSqlQuery query;
    if (user->role == User::Client) {
        query.prepare("UPDATE Client SET hash_password = ? WHERE id = ?");
    }
    else {
        query.prepare("UPDATE Employee SET hash_password = ? WHERE id = ?");
    }
    query.bindValue(0, hash_password);
    query.bindValue(1, user->id);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
}

void UserService::updateEmployee(const QSharedPointer<User> &employee) {
    QSqlQuery query;
    query.prepare("UPDATE Employee SET surname = ?, name = ?, patronymic = ?, phone = ? WHERE id = ?");
    query.bindValue(0, employee->surname);
    query.bindValue(1, employee->name);
    query.bindValue(2, employee->patronymic);
    query.bindValue(3, employee->phone);
    query.bindValue(4, employee->id);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
}

void UserService::updateClient(const QSharedPointer<User> &client) {
    QSqlQuery query;
    query.prepare("UPDATE Client SET surname = ?, name = ?, patronymic = ?, phone = ?, address = ? WHERE id = ?");
    query.bindValue(0, client->surname);
    query.bindValue(1, client->name);
    query.bindValue(2, client->patronymic);
    query.bindValue(3, client->phone);
    query.bindValue(4, client->address);
    query.bindValue(5, client->id);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
}

void UserService::removeEmployeeById(const int id) {
    QSqlQuery query;
    query.prepare("UPDATE Employee SET activity_flag = 0 WHERE id = ?");
    query.bindValue(0, id);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
}
