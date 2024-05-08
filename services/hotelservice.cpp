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
                                "City.id AS 'city_id',"
                                "City.title AS 'city_title',"
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
    hotel->city->title = record.value("city_title").toString();
    hotel->city->id = record.value("id_city").toInt();
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
    query.prepare("SELECT Hotel.id AS 'id', "
                         "Hotel.title AS 'hotel_title', "
                         "Hotel.id_city AS 'id_city', "
                         "City.title AS 'city_title', "
                         "Hotel.address AS 'address', "
                         "Hotel.category AS 'category' "
                  "FROM Hotel "
                        "JOIN City ON Hotel.id_city = City.id "
                  "WHERE (Hotel.activity_flag = 1) AND (hotel_title LIKE :t) "
                            "AND (category = :ctg OR :ctg = '') AND (id_city = :idc OR :idc = '');");
    query.bindValue(":t", filter["title"] + "%");
    query.bindValue(":ctg", filter["category"]);
    query.bindValue(":idc", filter["id_city"]);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
    return this->getHotelListByQuery(query);
}

QVector<QSharedPointer<Hotel>> HotelService::getHotelListByCityId(const int id) {
    QSqlQuery query;
    query.prepare("SELECT Hotel.id,"
                         "Hotel.title AS 'hotel_title',"
                         "City.id AS 'city_id',"
                         "City.title AS 'city_title',"
                         "Hotel.address,"
                         "Hotel.category "
                    "FROM Hotel "
                        "JOIN City ON Hotel.id_city = City.id "
                    "WHERE Hotel.activity_flag = 1 AND Hotel.id_city = ?;");
    query.bindValue(0, id);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
    return this->getHotelListByQuery(query);
}
