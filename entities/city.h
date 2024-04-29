#ifndef CITY_H
#define CITY_H

#include <QString>

class City
{
public:
    City();
    City(const int id, const QString &title, const QString &description);
    int id;
    QString title;
    QString climate;
};

#endif // CITY_H
