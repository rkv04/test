#include "cityservice.h"
#include "criticaldb.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

CityService::CityService() {}

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
