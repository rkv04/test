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
    QVector<QSharedPointer<Hotel>> getHotelList();
    int addHotel(const QSharedPointer<Hotel> &hotel);
    void removeHotelById(const int id);
    void updateHotel(const QSharedPointer<Hotel> &hotel);
    QVector<QSharedPointer<Hotel>> getHotelListByFilter(const QMap<QString, QString> &filter);
private:
    int getIdLastAddedHotel();
    QVector<QSharedPointer<Hotel>> getHotelListByQuery(QSqlQuery &query);
    QSharedPointer<Hotel> createHotelByRow(const QSqlRecord &record);
};

#endif // HOTELSERVICE_H
