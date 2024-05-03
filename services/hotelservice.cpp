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

QVector<QSharedPointer<Hotel>> HotelService::getHotelList() {
    QSqlQuery query;
    QString text_query = "SELECT Hotel.id,"
                                "Hotel.title AS 'hotel_title',"
                                "City.id AS 'city_id',"
                                "City.title AS 'city_title',"
                                "Hotel.address,"
                                "Hotel.category "
                         "FROM Hotel "
                            "JOIN City ON Hotel.id_city = City.id;";
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
    hotel->city->id = record.value("city_id").toInt();
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
