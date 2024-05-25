#ifndef TICKET_H
#define TICKET_H

#include <QDate>

#include "hotel.h"
#include "city.h"

class Ticket
{
public:
    Ticket();
    int id;
    unsigned long long price;
    int quantity;
    QDate departure_date;
    QSharedPointer<City> departure_city;
    QSharedPointer<Hotel> hotel;
    int duration;
    QString travel_time;
};

#endif // TICKET_H
