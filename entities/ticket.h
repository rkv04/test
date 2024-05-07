#ifndef TICKET_H
#define TICKET_H

#include "hotel.h"
#include "city.h"

class Ticket
{
public:
    Ticket();
    int id;
    int price;
    int quantity;
    QString departure_date;
    QSharedPointer<City> departure_city;
    QSharedPointer<Hotel> hotel;
    int duration;
    int travel_time;
};

#endif // TICKET_H
