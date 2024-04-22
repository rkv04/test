#ifndef APPDB_H
#define APPDB_H

#include <QSqlDatabase>
#include <QPair>
#include "client.h"

class AppDB {

public:
    static AppDB* getInstance();
    static void init();
    void addClient(Client &client);
    QSqlQuery getAllClients();
    QSqlQuery getClientsByFilter(const QString &surname, const QString &name, const QString &patronymic, const QString &phone) const;
    QPair<int, int> login(const QString phone, const QString password);

private:
    AppDB();
    static AppDB *instance;
    QSqlDatabase *db;
};

#endif // APPDB_H
