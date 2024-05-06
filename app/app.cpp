#include "app.h"
#include "db.h"
#include "userservice.h"
#include "criticaldb.h"
#include "apperror.h"
#include "user.h"
#include "context.h"
#include "log.h"

#include <QMessageBox>
#include <QCryptographicHash>

App* App::instance = nullptr;

App::App() {
    this->user_service = QSharedPointer<UserService>(new UserService());
    this->city_service = QSharedPointer<CityService>(new CityService());
    this->hotel_service = QSharedPointer<HotelService>(new HotelService());
}

App::~App() {}


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
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
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
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}


void App::createClient(const QSharedPointer<User> &client) {
    if (this->user_service->getClientByPhone(client->phone) != nullptr) {
        throw AppError("Пользователь с таким номером телефона уже существует", false);
    }
    client->password = QCryptographicHash::hash(client->password.toUtf8(), QCryptographicHash::Sha256).toHex();
    try {
        this->user_service->addClient(client);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }

}

QVector<QSharedPointer<User>> App::getClientsList() {
    try {
        return this->user_service->getClientList();
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

void App::setDiscount(const int client_id, const int discount) {
    try {
        this->user_service->setDiscountById(client_id, discount);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

QVector<QSharedPointer<User>> App::getClientsListByFilter(const QMap<QString, QString> &filter) {
    try {
        return this->user_service->getClientsByFilter(filter);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

int App::createCity(const QSharedPointer<City> &city) {
    try {
        return this->city_service->addCity(city);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

QVector<QSharedPointer<City>> App::getCityList() {
    try {
        return this->city_service->getCityList();
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

void App::removeCity(const QSharedPointer<City> &city) {
    try {
        this->city_service->removeCityById(city->id);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

void App::updateCity(const QSharedPointer<City> &city) {
    try {
        this->city_service->updateCity(city);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

QVector<QSharedPointer<City>> App::getCityListByFilter(const QString &title) {
    try {
        return this->city_service->getCityListByFilter(title);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

QVector<QSharedPointer<Hotel>> App::getHotelList() {
    try {
        return this->hotel_service->getHotelList();
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

int App::createHotel(const QSharedPointer<Hotel> &hotel) {
    try {
        return this->hotel_service->addHotel(hotel);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

void App::removeHotel(const QSharedPointer<Hotel> &hotel) {
    try {
        this->hotel_service->removeHotelById(hotel->id);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

void App::updateHotel(const QSharedPointer<Hotel> &hotel) {
    try {
        this->hotel_service->updateHotel(hotel);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

QVector<QSharedPointer<Hotel>> App::getHotelListByFilter(const QMap<QString, QString> &filter) {
    try {
        return this->hotel_service->getHotelListByFilter(filter);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}
