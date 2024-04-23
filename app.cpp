#include "app.h"
#include "userservice.h"
#include "criticaldb.h"
#include "client.h"

#include <QMessageBox>

App* App::instance = nullptr;

App::App() {
    this->user_service = new UserService();
}

App::~App() {
    delete this->user_service;
}

App* App::getInstance() {
    if (instance == nullptr) {
        return (new App());
    }
    else {
        return instance;
    }
}

int App::login(const QString &phone, const QString &password) {
    if (this->user_service->checkUserExistsByPhone(phone)) {
        int role = this->user_service->getRoleByPhone(phone);
        return role;
    }
    return -1;
}

void App::createClient(Client &client) {
    if (this->user_service->checkClientExistsByPhone(client.getPhone())) {
        throw QString("Пользователь с таким номером телефона уже существует");
    }
    try {
        this->user_service->addClient(client);
    }
    catch(const CriticalDB &ex) {
        // writing in the log.txt
        QMessageBox::critical(nullptr, "Tour operator", ex.what());
        exit(-1);
    }
}

