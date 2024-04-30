#ifndef HOTEL_H
#define HOTEL_H

#include <QString>

class Hotel
{
public:
    Hotel();
    Hotel(const int id, const QString &city_title, const QString &title, const int category, const QString &address);
    int id;
    QString city_title;
    QString title;
    int category;
    QString address;
};

#endif // HOTEL_H
