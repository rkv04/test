#include "cityservice.h"
#include "criticaldb.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

CityService::CityService() {}

int CityService::addCity(const QSharedPointer<City> city) {
    QSqlQuery query;
    query.prepare("INSERT INTO City (title, climate) VALUES (?, ?);");
    query.bindValue(0, city->title);
    query.bindValue(1, city->climate);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
    return this->getIdLastAddedCity();
}

void CityService::removeCityById(const int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM City WHERE id = ?;");
    query.bindValue(0, id);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
}

int CityService::getIdLastAddedCity() {
    QSqlQuery query;
    QString text_query = "SELECT id FROM City ORDER BY id DESC LIMIT 1;";
    if (!query.exec(text_query)) {
        throw CriticalDB(query.lastError().text());
    }
    query.first();
    return query.value("id").toInt();
}

QVector<QSharedPointer<City>> CityService::getCityList() {
    QSqlQuery query;
    QString text_query = "SELECT * FROM City;";
    if (!query.exec(text_query)) {
        throw CriticalDB(query.lastError().text());
    }
    return this->getCityListByQuery(query);
}

QVector<QSharedPointer<City>> CityService::getCityListByQuery(QSqlQuery &query) {
    QVector<QSharedPointer<City>> cities;
    while (query.next()) {
        auto city = this->createCityByRow(query.record());
        cities.append(city);
    }
    return cities;
}

QSharedPointer<City> CityService::createCityByRow(const QSqlRecord &record) {
    auto city = QSharedPointer<City>(new City());
    city->id = record.value("id").toInt();
    city->title = record.value("title").toString();
    city->climate = record.value("climate").toString();
    return city;
}
