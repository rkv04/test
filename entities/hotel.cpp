#include "hotel.h"

Hotel::Hotel() {
    this->id = -1;
    this->city_title = QString();
    this->title = QString();
    this->category = -1;
    this->address = QString();
}

Hotel::Hotel(const int id, const QString &city_title, const QString &title, const int category, const QString &address) {
    this->id = id;
    this->city_title = city_title;
    this->title = title;
    this->category = category;
    this->address = address;
}

