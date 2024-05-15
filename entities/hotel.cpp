#include "hotel.h"

#include <QDebug>

Hotel::Hotel() {
    this->id = -1;
    this->title = QString();
    this->category = -1;
    this->address = QString();
    this->city = nullptr;
}
