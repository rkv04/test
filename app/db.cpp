#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QTextStream>
#include <QSqlError>
#include <QStringList>
#include <QCryptographicHash>

#include "db.h"
#include "criticaldb.h"

DB::DB() {}

void DB::init() {
    QSqlDatabase app_db = QSqlDatabase::addDatabase("QSQLITE");
    app_db.setDatabaseName("./app_db.db");

    if (!app_db.open()) {
        throw CriticalDB(app_db.lastError().text());
    }

    QFile file("./db_script.sql");
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
    if (!query.exec("SELECT * FROM Employee")) {
        throw CriticalDB(query.lastError().text());
    }
    if (query.first()) {
        return;
    }
    QString phone = "1";
    QString password = "1";
    QString hash_password = QCryptographicHash::hash(QString(password).toUtf8(), QCryptographicHash::Sha256).toHex();
    query.prepare("INSERT INTO Employee (phone, hash_password, surname, name) VALUES (?, ?, 'Employee', 'Employee');");
    query.bindValue(0, phone);
    query.bindValue(1, hash_password);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
}
