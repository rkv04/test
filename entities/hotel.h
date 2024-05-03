#ifndef HOTEL_H
#define HOTEL_H

#include <QString>
#include <QSharedPointer>

#include "city.h"

class Hotel
{
public:
    Hotel();
    int id;
    QString title;
    int category;
    QString address;
    QSharedPointer<City> city;
};

#endif // HOTEL_H
