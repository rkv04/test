#ifndef USERSERVICE_H
#define USERSERVICE_H

#include "user.h"

#include <QSqlQuery>
#include <QSharedPointer>
#include <QVector>

class UserService
{
public:
    UserService();

    QSharedPointer<User> getClientByPhone(const QString &phone);
    QVector<QSharedPointer<User>> getClientList();
    QVector<QSharedPointer<User>> getClientsByFilter(const QMap<QString, QString> &filter);
    void setDiscountById(const int id_client, const int discount);
    QSharedPointer<User> getEmployeeByPhone(const QString &phone);
    void addClient(const User &client);

private:

    QVector<QSharedPointer<User>> getClientListByQuery(QSqlQuery &query);
    QSharedPointer<User> createClientByRow(const QSqlRecord &record);
    QSharedPointer<User> createEmployeeByRow(const QSqlRecord &record);

};

#endif // USERSERVICE_H
