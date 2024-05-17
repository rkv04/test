#ifndef APP_H
#define APP_H

#include <QSharedPointer>

#include "userservice.h"
#include "cityservice.h"
#include "hotelservice.h"
#include "ticketservice.h"
#include "dealservice.h"

#include "user.h"
#include "city.h"
#include "hotel.h"
#include "ticket.h"
#include "deal.h"


class App {

public:

    inline static const QString APPLICATION_NAME = "Tour operator";

    static App* getInstance();
    void init();

    void createClient(const QSharedPointer<User> &client);
    QSharedPointer<User> login(const QString &phone, const QString &password);
    QVector<QSharedPointer<User>> getClientsList();
    QVector<QSharedPointer<User>> getClientsListByFilter(const QMap<QString, QString> &filter);
    void setDiscount(const int client_id, const int discount);
    void updateCLient(const QSharedPointer<User> &client);

    int createEmployee(const QSharedPointer<User> &employee);
    void updateEmployee(const QSharedPointer<User> &employee);
    QVector<QSharedPointer<User>> getEmployeeList();
    void updateUserPassword(const QSharedPointer<User> &user, const QString &password);

    int createCity(const QSharedPointer<City> &city);
    void removeCity(const QSharedPointer<City> &city);
    void updateCity(const QSharedPointer<City> &city);
    QVector<QSharedPointer<City>> getCityList();
    QVector<QSharedPointer<City>> getCityListByFilter(const QString &title);

    int createHotel(const QSharedPointer<Hotel> &hotel);
    void removeHotel(const QSharedPointer<Hotel> &hotel);
    void updateHotel(const QSharedPointer<Hotel> &hotel);
    QVector<QSharedPointer<Hotel>> getHotelsByCity(const QSharedPointer<City> &city);
    QVector<QSharedPointer<Hotel>> getHotelList();
    QVector<QSharedPointer<Hotel>> getHotelListByFilter(const QMap<QString, QString> &filter);

    int createTicket(const QSharedPointer<Ticket> &ticket);
    void removeTicket(const QSharedPointer<Ticket> &ticket);
    void updateTicket(const QSharedPointer<Ticket> &ticket);
    QVector<QSharedPointer<Ticket>> getTicketList();
    QVector<QSharedPointer<Ticket>> getTicketsAvailableForPurchase();
    QVector<QSharedPointer<Ticket>> getTicketListByListIds(const QStringList &ids);
    QVector<QSharedPointer<Ticket>> getTicketListByFilter(const QMap<QString, QString> &filter);

    void buyTicket(const QSharedPointer<Ticket> &ticket, const int quantity);
    QVector<QSharedPointer<Deal>> getDealListByClient(const QSharedPointer<User> &client);

private:

    App();
    ~App();
    static App *instance;

    QSharedPointer<User> tryLoginAsClient(const QString &phone, const QString &password);
    QSharedPointer<User> tryLoginAsEmployee(const QString &phone, const QString &password);

    QSharedPointer<UserService> user_service;
    QSharedPointer<CityService> city_service;
    QSharedPointer<HotelService> hotel_service;
    QSharedPointer<TicketService> ticket_service;
    QSharedPointer<DealService> deal_service;

};

#endif // APP_H
