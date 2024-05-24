#ifndef TICKET_H
#define TICKET_H

#include "hotel.h"
#include "city.h"

class Ticket
{
public:
    Ticket();
    int id;
    unsigned long long price;
    int quantity;
    QString departure_date;
    QSharedPointer<City> departure_city;
    QSharedPointer<Hotel> hotel;
    int duration;
    QString travel_time;
};

#endif // TICKET_H
