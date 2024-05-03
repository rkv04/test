#ifndef APP_H
#define APP_H

#include <QSharedPointer>

#include "userservice.h"
#include "cityservice.h"
#include "hotelservice.h"
#include "user.h"
#include "city.h"
#include "hotel.h"


class App {

public:

    inline static const QString APPLICATION_NAME = "Tour operator";

    static App* getInstance();
    void init();

    void createClient(User &client);
    QSharedPointer<User> login(const QString &phone, const QString &password);
    QVector<QSharedPointer<User>> getClientsList();
    QVector<QSharedPointer<User>> getClientsListByFilter(const QMap<QString, QString> &filter);
    void setDiscount(const int client_id, const int discount);

    int createCity(const QSharedPointer<City> city);
    void removeCity(const QSharedPointer<City> city);
    void updateCity(const QSharedPointer<City> city);
    QVector<QSharedPointer<City>> getCityList();
    QVector<QSharedPointer<City>> getCityListByFilter(const QString &title);

    QVector<QSharedPointer<Hotel>> getHotelList();
    int createHotel(const QSharedPointer<Hotel> &hotel);

private:

    App();
    ~App();
    static App *instance;

    QSharedPointer<User> tryLoginAsClient(const QString &phone, const QString &password);
    QSharedPointer<User> tryLoginAsEmployee(const QString &phone, const QString &password);

    QSharedPointer<UserService> user_service;
    QSharedPointer<CityService> city_service;
    QSharedPointer<HotelService> hotel_service;

};

#endif // APP_H
