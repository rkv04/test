#include "app.h"
#include "db.h"
#include "userservice.h"
#include "criticaldb.h"
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
    QString hash_password = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    QSharedPointer<User> client = this->tryLoginAsClient(phone, password);
    if (client != nullptr && client->hash_password == hash_password) {
        Context::setContext(client->id);
        return client;
    }
    QSharedPointer<User> employeee = this->tryLoginAsEmployee(phone, password);
    if (employeee != nullptr && employeee->hash_password == hash_password) {
        Context::setContext(employeee->id);
        return employeee;
    }
    throw QString("Введён неверный логин или пароль");
}

QSharedPointer<User> App::tryLoginAsClient(const QString &phone, const QString &password) {
    try {
        QSharedPointer<User> client = this->user_service->getClientByPhone(phone);
        return client;
    }
    catch(const CriticalDB &ex) {
        // TO DO writing in the log.txt
        QMessageBox::critical(nullptr, "Tour operator", ex.what());
        exit(-1);
    }
}

QSharedPointer<User> App::tryLoginAsEmployee(const QString &phone, const QString &password) {
    try {
        QSharedPointer<User> employee = this->user_service->getEmployeeByPhone(phone);
        return employee;
    }
    catch(const CriticalDB &ex) {
        // TO DO writing in the log.txt
        QMessageBox::critical(nullptr, "Tour operator", ex.what());
        exit(-1);
    }
}


void App::createClient(User &client) {
    if (this->user_service->getClientByPhone(client.phone) != nullptr) {
        throw QString("Пользователь с таким номером телефона уже существует");
    }
    try {
        this->user_service->addClient(client);
    }
    catch(const CriticalDB &ex) {
        // TO DO writing in the log.txt
        QMessageBox::critical(nullptr, "Tour operator", ex.what());
        exit(-1);
    }

}

