#ifndef HOTEL_H
#define HOTEL_H

#include <QString>

class Hotel
{
public:
    Hotel();
    Hotel(const int id, const int id_city, const QString &title, const int category, const QString &address);
    int id;
    int id_city;
    QString title;
    int category;
    QString address;
};

#endif // HOTEL_H
