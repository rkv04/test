#include "hotelservice.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "criticaldb.h"

HotelService::HotelService() {}

QVector<QSharedPointer<Hotel>> HotelService::getHotelList() {
    QSqlQuery query;
    QString text_query = "SELECT Hotel.id,"
                                "Hotel.title AS 'hotel_title',"
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
    hotel->id = record.value("id").toInt();
    hotel->title = record.value("hotel_title").toString();
    hotel->city_title = record.value("city_title").toString();
    hotel->address = record.value("address").toString();
    hotel->category = record.value("category").toInt();
    return hotel;
}
