#ifndef APP_H
#define APP_H

#include <QSharedPointer>

#include "userservice.h"
#include "user.h"


class App {

public:

    static App* getInstance();
    void init();

    void createClient(User &client);
    QSharedPointer<User> login(const QString &phone, const QString &password);
    QVector<QSharedPointer<User>> getClientsList();
    void setDiscount(const int client_id, const int discount);

    // void createCity();
    // void createHotel();
    // void createTicket();

private:
    App();
    ~App();
    static App *instance;

    QSharedPointer<User> tryLoginAsClient(const QString &phone, const QString &password);
    QSharedPointer<User> tryLoginAsEmployee(const QString &phone, const QString &password);

    UserService *user_service;

};

#endif // APP_H
