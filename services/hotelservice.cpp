#include "hotelservice.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "criticaldb.h"

HotelService::HotelService() {}

int HotelService::addHotel(const QSharedPointer<Hotel> &hotel) {
    QSqlQuery query;
    query.prepare("INSERT INTO Hotel (id_city, title, address, category) VALUES (?, ?, ?, ?);");
    query.bindValue(0, hotel->city->id);
    query.bindValue(1, hotel->title);
    query.bindValue(2, hotel->address);
    query.bindValue(3, hotel->category);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
    return this->getIdLastAddedHotel();
}

void HotelService::removeHotelById(const int id) {
    QSqlQuery query;
    query.prepare("UPDATE Hotel SET activity_flag = 0 WHERE id = ?;");
    query.bindValue(0, id);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
}

void HotelService::updateHotel(const QSharedPointer<Hotel> &hotel) {
    QSqlQuery query;
    query.prepare("UPDATE Hotel SET id_city = ?, title = ?, category = ?, address = ? WHERE id = ?;");
    query.bindValue(0, hotel->city->id);
    query.bindValue(1, hotel->title);
    query.bindValue(2, hotel->category);
    query.bindValue(3, hotel->address);
    query.bindValue(4, hotel->id);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
}

QVector<QSharedPointer<Hotel>> HotelService::getHotelList() {
    QSqlQuery query;
    QString text_query = "SELECT Hotel.id,"
                                "Hotel.title AS 'hotel_title',"
                                "City.id AS 'id_city',"
                                "City.title AS 'city_title', "
                                "City.climate AS 'city_climate', "
                                "Hotel.address,"
                                "Hotel.category "
                         "FROM Hotel "
                            "JOIN City ON Hotel.id_city = City.id "
                         "WHERE Hotel.activity_flag = 1;";
    if (!query.exec(text_query)) {
        throw CriticalDB(query.lastError().text());
    }
    return this->getHotelListByQuery(query);
}

QVector<QSharedPointer<Hotel>> HotelService::getHotelListByQuery(QSqlQuery &query) {
    QVector<QSharedPointer<Hotel>> hotels;
    while (query.next()) {
        auto hotel = this->createHotelByRow(query.record());
        hotels.append(hotel);
    }
    return hotels;
}

QSharedPointer<Hotel> HotelService::createHotelByRow(const QSqlRecord &record) {
    auto hotel = QSharedPointer<Hotel>(new Hotel());
    hotel->city = QSharedPointer<City>(new City());
    hotel->id = record.value("id").toInt();
    hotel->title = record.value("hotel_title").toString();
    hotel->city->id = record.value("id_city").toInt();
    hotel->city->title = record.value("city_title").toString();
    hotel->city->climate = record.value("city_climate").toString();
    hotel->address = record.value("address").toString();
    hotel->category = record.value("category").toInt();
    return hotel;
}

int HotelService::getIdLastAddedHotel() {
    QSqlQuery query;
    QString text_query = "SELECT id FROM Hotel ORDER BY id DESC LIMIT 1;";
    if (!query.exec(text_query)) {
        throw CriticalDB(query.lastError().text());
    }
    query.first();
    return query.value("id").toInt();
}

QVector<QSharedPointer<Hotel>> HotelService::getHotelListByFilter(const QMap<QString, QString> &filter) {
    QSqlQuery query;
    QString text_query = "SELECT Hotel.id AS 'id', "
                         "Hotel.title AS 'hotel_title', "
                         "City.id AS 'id_city', "
                         "City.title AS 'city_title', "
                         "Hotel.address AS 'address', "
                         "Hotel.category AS 'category' "
                  "FROM Hotel "
                        "JOIN City ON Hotel.id_city = City.id "
                  "WHERE Hotel.activity_flag = 1 ";
    if (!filter["title"].isEmpty()) {
        text_query += " AND hotel_title LIKE :title";
    }
    if (!filter["category"].isEmpty()) {
        text_query += " AND category = :category";
    }
    if (!filter["id_city"].isEmpty()) {
        text_query += " AND id_city = :id_city";
    }
    query.prepare(text_query);
    QStringList keys = filter.keys();
    for (auto &key : keys) {
        query.bindValue(":" + key, filter[key]);
    }
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
    return this->getHotelListByQuery(query);
}

QVector<QSharedPointer<Hotel>> HotelService::getHotelListByCityId(const int id) {
    QSqlQuery query;
    query.prepare("SELECT Hotel.id,"
                         "Hotel.title AS 'hotel_title',"
                         "City.id AS 'id_city',"
                         "City.title AS 'city_title',"
                         "City.climate AS 'city_climate', "
                         "Hotel.address,"
                         "Hotel.category "
                    "FROM Hotel "
                        "JOIN City ON Hotel.id_city = City.id "
                    "WHERE Hotel.activity_flag = 1 AND City.id = ?;");
    query.bindValue(0, id);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
    return this->getHotelListByQuery(query);
}

QVector<QSharedPointer<Hotel>> HotelService::getHotelListByListIds(const QVector<int> &ids) {
    QString filter = "(";
    for (int i = 0; i < ids.size(); i++) {
        filter += QString::number(ids.at(i));
        if (i < ids.size() - 1) {
            filter += ", ";
        }
    }
    filter += ")";
    QSqlQuery query;
    QString text_query = "SELECT Hotel.id,"
                                "Hotel.title AS 'hotel_title',"
                                "City.id AS 'id_city',"
                                "City.title AS 'city_title', "
                                "City.climate AS 'city_climate', "
                                "Hotel.address,"
                                "Hotel.category "
                            "FROM Hotel "
                                "JOIN City ON Hotel.id_city = City.id "
                            "WHERE Hotel.id IN " + filter + " ORDER BY Hotel.title;";
    if (!query.exec(text_query)) {
        throw CriticalDB(query.lastError().text());
    }
    return this->getHotelListByQuery(query);
}

QVector<int> HotelService::getCitiesIdsFromHotels() {
    QSqlQuery query;
    QString text_query = "SELECT DISTINCT id_city FROM Hotel WHERE activity_flag = 1;";
    if (!query.exec(text_query)) {
        throw CriticalDB(query.lastError().text());
    }
    QVector<int> cities_ids;
    while (query.next()) {
        cities_ids.append(query.value("id_city").toInt());
    }
    return cities_ids;
}
