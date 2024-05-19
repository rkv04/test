#ifndef HOTELSERVICE_H
#define HOTELSERVICE_H

#include <QSharedPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMap>
#include "hotel.h"

class HotelService
{
public:
    HotelService();
    int addHotel(const QSharedPointer<Hotel> &hotel);
    QVector<QSharedPointer<Hotel>> getHotelList();
    void removeHotelById(const int id);
    void updateHotel(const QSharedPointer<Hotel> &hotel);
    QVector<QSharedPointer<Hotel>> getHotelListByCityId(const int id);
    QVector<QSharedPointer<Hotel>> getHotelListByFilter(const QMap<QString, QString> &filter);
    QVector<QSharedPointer<Hotel>> getHotelListByListIds(const QVector<int> &ids);

    QVector<int> getCitiesIdsFromHotels();
private:
    int getIdLastAddedHotel();
    QVector<QSharedPointer<Hotel>> getHotelListByQuery(QSqlQuery &query);
    QSharedPointer<Hotel> createHotelByRow(const QSqlRecord &record);
};

#endif // HOTELSERVICE_H
