#include "app.h"
#include "db.h"
#include "userservice.h"
#include "criticaldb.h"
#include "apperror.h"
#include "user.h"
#include "context.h"
#include "log.h"

#include <QDate>
#include <QMessageBox>
#include <QCryptographicHash>

App* App::instance = nullptr;

App::App() {
    this->user_service = QSharedPointer<UserService>(new UserService());
    this->city_service = QSharedPointer<CityService>(new CityService());
    this->hotel_service = QSharedPointer<HotelService>(new HotelService());
    this->ticket_service = QSharedPointer<TicketService>(new TicketService());
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

void App::handleAppError(const CriticalDB &ex) {
    Log::write(ex.what());
    throw AppError(CriticalDB::FATAL_MSG, true);
}

QSharedPointer<User> App::login(const QString &phone, const QString &password) {
    auto client = this->tryLoginAsClient(phone, password);
    if (client != nullptr) {
        Context::setContext(client);
        return client;
    }
    auto employeee = this->tryLoginAsEmployee(phone, password);
    if (employeee != nullptr) {
        Context::setContext(employeee);
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

void App::updateCLient(const QSharedPointer<User> &updated_client) {
    QSharedPointer<User> client = this->user_service->getClientByPhone(updated_client->phone);
    if (client != nullptr && updated_client->id != client->id) {
        throw AppError("Указанный номер телефона уже занят", false);
    }
    try {
        this->user_service->updateClient(client);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

int App::createEmployee(const QSharedPointer<User> &employee) {
    if (this->user_service->getEmployeeByPhone(employee->phone) != nullptr) {
        throw AppError("Сотрудник с таким номером телефона уже существует", false);
    }
    employee->password = QCryptographicHash::hash(employee->password.toUtf8(), QCryptographicHash::Sha256).toHex();
    try {
        return this->user_service->addEmployee(employee);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

void App::updateEmployee(const QSharedPointer<User> &updated_employee) {
    QSharedPointer<User> employee = this->user_service->getEmployeeByPhone(updated_employee->phone);
    if (employee != nullptr && updated_employee->id != employee->id) {
        throw AppError("Указанный номер телефона уже занят", false);
    }
    try {
        this->user_service->updateEmployee(updated_employee);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

void App::removeEmployee(const QSharedPointer<User> &employee) {
    try {
        this->user_service->removeEmployeeById(employee->id);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

QVector<QSharedPointer<User>> App::getEmployeeList() {
    try {
        return this->user_service->getEmployeeList();
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

void App::updateUserPassword(const QSharedPointer<User> &user, const QString &password) {
    const QString hash_password = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    try {
        this->user_service->updateUserPassword(user, hash_password);
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

QVector<QSharedPointer<Hotel>> App::getHotelsByCity(const QSharedPointer<City> &city) {
    try {
        return this->hotel_service->getHotelListByCityId(city->id);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

int App::createTicket(const QSharedPointer<Ticket> &ticket) {
    try {
        return this->ticket_service->addTicket(ticket);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

void App::removeTicket(const QSharedPointer<Ticket> &ticket) {
    try {
        this->ticket_service->removeTicketById(ticket->id);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

void App::updateTicket(const QSharedPointer<Ticket> &ticket) {
    try {
        this->ticket_service->updateTicket(ticket);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

QVector<QSharedPointer<Ticket>> App::getTicketList() {
    try {
        return this->ticket_service->getTicketList();
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

QVector<QSharedPointer<Ticket>> App::getTicketsAvailableForPurchase() {
    try {
        return this->ticket_service->getTicketsAvailableForPurchase();
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

QVector<QSharedPointer<Ticket>> App::getTicketListByFilter(const QMap<QString, QString> &filter) {
    try {
        return this->ticket_service->getTicketListByFilter(filter);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

QVector<QSharedPointer<Ticket>> App::getTicketListByListIds(const QStringList &ids) {
    try {
        return this->ticket_service->getTicketListByListIds(ids);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

QVector<QSharedPointer<City>> App::getDepartureCitiesFromTickets() {
    try {
        QVector<int> city_ids = this->ticket_service->getDepartureCitiesIdsFromTickets();
        return this->city_service->getCityListByListIds(city_ids);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

QVector<QSharedPointer<City>> App::getDestinationCitiesFromTickets() {
    try {
        QVector<int> cities_ids = this->ticket_service->getDestinationCitiesIdsFromTickets();
        return this->city_service->getCityListByListIds(cities_ids);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

QVector<QSharedPointer<City>> App::getCitiesFromHotels() {
    try {
        QVector<int> cities_ids = this->hotel_service->getCitiesIdsFromHotels();
        return this->city_service->getCityListByListIds(cities_ids);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

QVector<QSharedPointer<Hotel>> App::getHotelsFromTickets() {
    try {
        QVector<int> hotel_ids = this->ticket_service->getHotelsIdsFromTickets();
        return this->hotel_service->getHotelListByListIds(hotel_ids);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

QVector<QSharedPointer<Hotel>> App::getHotelsFromTicketsByCity(const QSharedPointer<City> &city) {
    try {
        QVector<int> hotels_ids = this->ticket_service->getHotelsIdsFromTicketsByIdCity(city->id);
        return this->hotel_service->getHotelListByListIds(hotels_ids);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

void App::buyTicket(const QSharedPointer<Ticket> &purchased_ticket, const int quantity) {
    auto cur_client = Context::getContext();
    QSharedPointer<Deal> deal = QSharedPointer<Deal>(new Deal());
    deal->date = QDate::currentDate().toString("dd.MM.yyyy");
    deal->ticket = purchased_ticket;
    deal->id_client = cur_client->id;
    deal->discount = cur_client->discount;
    deal->quantity = quantity;
    deal->deal_sum = purchased_ticket->price * quantity * (100 - cur_client->discount) / 100; // TODO
    try {
        auto ticket = this->ticket_service->getTicketById(purchased_ticket->id);
        if (ticket->quantity < quantity) {
            throw AppError("Указанное количество путевок превышает имеющееся количество в продаже", false);
        }
        this->deal_service->addDeal(deal);
        this->ticket_service->setQuantityById(purchased_ticket->id, ticket->quantity - quantity); // TODO
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}

QVector<QSharedPointer<Deal>> App::getDealListByClient(const QSharedPointer<User> &client) {
    try {
        return this->deal_service->getDealListByIdClient(client->id);
    }
    catch(const CriticalDB &ex) {
        Log::write(ex.what());
        throw AppError(CriticalDB::FATAL_MSG, true);
    }
}
