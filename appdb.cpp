#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QTextStream>
#include <QSqlError>
#include <QStringList>
#include <QPair>

#include "criticaldb.h"
#include "appdb.h"

AppDB *AppDB::instance = nullptr;

AppDB::AppDB() {
    QSqlDatabase app_db = QSqlDatabase::addDatabase("QSQLITE");
    app_db.setDatabaseName("C:/Tour operator/build-tour_operator-Desktop_Qt_6_5_3_MinGW_64_bit-Debug/database/app_db.db");

    if (!app_db.open()) {
        throw CriticalDB("Ошибка при открытии соединения с базой данных");
    }

    QFile file("C:/Tour operator/build-tour_operator-Desktop_Qt_6_5_3_MinGW_64_bit-Debug/database/db_script.sql");
    if (!file.open(QIODevice::ReadOnly)) {
        throw CriticalDB("Ошибка при открытии скрипта развёртывания базы данных");
    }
    QTextStream ist(&file);
    QStringList scriptQueries = ist.readAll().split(';');
    QSqlQuery query(app_db);

    foreach (QString textQuery, scriptQueries) {
        if (textQuery.trimmed().isEmpty()) {
            continue;
        }
        if (!query.exec(textQuery))
        {
            throw CriticalDB(query.lastError().text());
        }
    }
}

void AppDB::init() {
    if (instance == nullptr) {
        instance = new AppDB();
    }
}

AppDB* AppDB::getInstance() {
    if (instance == nullptr) {
        instance = new AppDB();
    }
    return instance;
}

// void AppDB::addClient(Client &client) {
//     QSqlQuery query;
//     query.prepare("SELECT phone FROM Client WHERE phone = ?;");
//     query.bindValue(0, client.getPhone());
//     query.exec();
//     if (query.first()) {
//         throw QString("Пользователь с таким номером телефона уже существует");
//     }
//     query.prepare("INSERT INTO Client (phone, name, surname, patronymic, hash_password) VALUES (?, ?, ?, ?, ?);");
//     query.bindValue(0, client.getPhone());
//     query.bindValue(1, client.getName());
//     query.bindValue(2, client.getSurname());
//     query.bindValue(3, client.getPatronymic());
//     query.bindValue(4, client.getHashPassword());
//     if (!query.exec()) {
//         throw CriticalDB(query.lastError().text());
//     }
// }

QPair<int, int> AppDB::login(const QString phone, const QString hash_password) {
    QSqlQuery query;
    query.prepare("SELECT id, role FROM Client WHERE phone = ? AND hash_password = ?;");
    query.bindValue(0, phone);
    query.bindValue(1, hash_password);

    if (!query.exec()) {
        throw CriticalDB(query.lastError().databaseText());
    }
    if (query.first()) {
        QPair<int, int> idAndRole;
        idAndRole.first = query.value("id").toInt();
        idAndRole.second = query.value("role").toInt();
        return idAndRole;
    }

    query.prepare("SELECT id, role FROM Employee WHERE phone = ? AND hash_password = ?;");
    query.bindValue(0, phone);
    query.bindValue(1, hash_password);

    if (!query.exec()) {
        throw CriticalDB(query.lastError().databaseText());
    }
    if (query.first()) {
        QPair<int, int> idAndRole;
        idAndRole.first = query.value("id").toInt();
        idAndRole.second = query.value("role").toInt();
        return idAndRole;
    }
    throw QString("Указан неверный телефон или пароль");
}

QSqlQuery AppDB::getAllClients() {
    QSqlQuery query;
    QString text_query = "SELECT surname AS 'Фамилия',"
                                "name AS 'Имя',"
                                "patronymic AS 'Отчество',"
                                "phone AS 'Телефон',"
                                "amount_of_purchased_tickets AS 'Путёвок куплено',"
                                "discount AS 'Скидка'"
                         "FROM Client;";
    if (!query.exec(text_query)) {
        throw CriticalDB(query.lastError().text());
    }
    return query;
}

QSqlQuery AppDB::getClientsByFilter(const QString &surname, const QString &name, const QString &patronymic, const QString &phone) const {
    QSqlQuery query;
    query.prepare("SELECT surname AS 'Фамилия',"
                         "name AS 'Имя',"
                         "patronymic AS 'Отчество',"
                         "phone AS 'Телефон',"
                         "amount_of_purchased_tickets AS 'Путёвок куплено',"
                         "discount AS 'Скидка'"
                    "FROM Client "
                  "WHERE (surname = :s OR :s = '') AND (name = :n OR :n = '') AND (patronymic = :pt OR :pt = '') AND (phone = :ph OR :ph = '');");
    query.bindValue(":s", surname);
    query.bindValue(":n", name);
    query.bindValue(":pt", patronymic);
    query.bindValue(":ph", phone);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
    return query;
}

