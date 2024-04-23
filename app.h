#ifndef APP_H
#define APP_H

#include "userservice.h"

class App {

public:

    static App* getInstance();

    void createClient(Client &client);
    void createEmployee();
    // void createCity();
    // void createHotel();
    // void createTicket();

    int login(const QString &phone, const QString &password);

private:
    App();
    ~App();
    static App *instance;

    UserService *user_service;

};

#endif // APP_H
