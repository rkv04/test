#include "ticket.h"

#include <QDebug>

Ticket::Ticket() {
    this->id = -1;
    this->price = -1;
    this->duration = -1;
    this->travel_time = QString();
    this->departure_date = QDate();
    this->hotel = nullptr;
    this->departure_city = nullptr;
}
