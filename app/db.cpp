#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QTextStream>
#include <QSqlError>
#include <QStringList>

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
}
