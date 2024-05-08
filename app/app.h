#ifndef APP_H
#define APP_H

#include <QSharedPointer>

#include "userservice.h"
#include "cityservice.h"
#include "hotelservice.h"
#include "ticketservice.h"

#include "user.h"
#include "city.h"
#include "hotel.h"
#include "ticket.h"


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
    QVector<QSharedPointer<Ticket>> getTicketListByFilter(const QMap<QString, QString> &filter);

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

};

#endif // APP_H
