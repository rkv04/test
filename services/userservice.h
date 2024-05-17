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

    void addClient(const QSharedPointer<User> &client);
    QSharedPointer<User> getClientByPhone(const QString &phone);
    QVector<QSharedPointer<User>> getClientList();
    QVector<QSharedPointer<User>> getClientsByFilter(const QMap<QString, QString> &filter);
    void setDiscountById(const int id_client, const int discount);
    void updateClient(const QSharedPointer<User> &client);

    int addEmployee(const QSharedPointer<User> &employee);
    void removeEmployeeById(const int id);
    void updateEmployee(const QSharedPointer<User> &employee);
    QSharedPointer<User> getEmployeeByPhone(const QString &phone);
    QVector<QSharedPointer<User>> getEmployeeList();

    void updateUserPassword(const QSharedPointer<User> &user , const QString &hash_password);

private:

    int getIdLastAddedEmployee();
    QVector<QSharedPointer<User>> getClientListByQuery(QSqlQuery &query);
    QVector<QSharedPointer<User>> getEmployeeListByQuery(QSqlQuery &query);
    QSharedPointer<User> createClientByRow(const QSqlRecord &record);
    QSharedPointer<User> createEmployeeByRow(const QSqlRecord &record);

};

#endif // USERSERVICE_H
