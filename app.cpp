#include "app.h"
#include "db.h"
#include "userservice.h"
#include "criticaldb.h"
#include "apperror.h"
#include "user.h"
#include "context.h"

#include <QMessageBox>
#include <QCryptographicHash>

App* App::instance = nullptr;

App::App() {
    this->user_service = new UserService();
}

App::~App() {
    delete user_service;
}

App* App::getInstance() {
    if (instance == nullptr) {
        return (new App());
    }
    else {
        return instance;
    }
}

void App::init() {
    DB::init();
}

QSharedPointer<User> App::login(const QString &phone, const QString &password) {
    auto client = this->tryLoginAsClient(phone, password);
    if (client != nullptr) {
        Context::setContext(client->id);
        return client;
    }
    auto employeee = this->tryLoginAsEmployee(phone, password);
    if (employeee != nullptr) {
        Context::setContext(employeee->id);
        return employeee;
    }
    throw AppError("Введён неверный логин или пароль", false);
}

QSharedPointer<User> App::tryLoginAsClient(const QString &phone, const QString &password) {
    QString hash_password = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    try {
        auto client = this->user_service->getClientByPhone(phone);
        if (client != nullptr && client->password == hash_password) {
            return client;
        }
        return nullptr;
    }
    catch(const CriticalDB &ex) {
        // TO DO writing in the log.txt
        throw AppError("Критическая ошибка! См. log.txt", true);
    }
}

QSharedPointer<User> App::tryLoginAsEmployee(const QString &phone, const QString &password) {
    QString hash_password = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    try {
        auto employee = this->user_service->getEmployeeByPhone(phone);
        if (employee != nullptr && employee->password == hash_password) {
            return employee;
        }
        return nullptr;
    }
    catch(const CriticalDB &ex) {
        // TO DO writing in the log.txt
        throw AppError("Критическая ошибка! См. log.txt", true);
    }
}


void App::createClient(User &client) {
    if (this->user_service->getClientByPhone(client.phone) != nullptr) {
        throw AppError("Пользователь с таким номером телефона уже существует", false);
    }
    client.password = QCryptographicHash::hash(client.password.toUtf8(), QCryptographicHash::Sha256).toHex();
    try {
        this->user_service->addClient(client);
    }
    catch(const CriticalDB &ex) {
        // TO DO writing in the log.txt
        throw AppError("Критическая ошибка! См. log.txt", true);
    }

}

QSqlQuery App::getClientsList() {
    try {
        return this->user_service->getAllClients();
    }
    catch(const CriticalDB &ex) {
        // TO DO writing in the log.txt
        throw AppError("Критическая ошибка! См. log.txt", true);
    }
}

void App::setDiscount(const int client_id, const int discount) {
    try {
        this->user_service->setDiscountById(client_id, discount);
    }
    catch(const CriticalDB &ex) {
        // TO DO writing in the log.txt
        throw AppError("Критическая ошибка! См. log.txt", true);
    }
}
