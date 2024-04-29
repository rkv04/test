#include "hotel.h"

Hotel::Hotel() {
    this->id = -1;
    this->id_city = -1;
    this->title = QString();
    this->category = -1;
    this->address = QString();
}

Hotel::Hotel(const int id, const int id_city, const QString &title, const int category, const QString &address) {
    this->id = id;
    this->id_city = id_city;
    this->title = title;
    this->category = category;
    this->address = address;
}

