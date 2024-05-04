#include "hotelmodel.h"

#include <QVariant>

HotelModel::HotelModel(QObject *parent)
    : QAbstractTableModel{parent}
{}

int HotelModel::rowCount(const QModelIndex &) const {
    return this->hotels.size();
}

int HotelModel::columnCount(const QModelIndex &) const {
    return 4;
}

QVariant HotelModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        switch(index.column()) {
        case 0:
            return this->hotels.at(index.row())->title;
        case 1:
            return this->hotels.at(index.row())->category;
        case 2:
            return this->hotels.at(index.row())->city->title;
        case 3:
            return this->hotels.at(index.row())->address;
        }
    }
    return QVariant();
}

QVariant HotelModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            return this->headers.at(section);
        }
        if (orientation == Qt::Vertical) {
            return QString::number(section);
        }
    }
    return QVariant();
}


void HotelModel::setHotelsList(const QVector<QSharedPointer<Hotel>> &hotels) {
    this->beginResetModel();
    this->hotels = hotels;
    this->endResetModel();
}

void HotelModel::addHotel(const QSharedPointer<Hotel> &hotel) {
    this->hotels.append(hotel);
    emit layoutChanged();
}

QVector<QSharedPointer<City>> HotelModel::getHotelCities() {
    QSet<QString> unique_city_title;
    QVector<QSharedPointer<City>> hotel_cities;
    for (auto hotel : this->hotels) {
        if (!unique_city_title.contains(hotel->city->title)) {
            unique_city_title.insert(hotel->city->title);
            hotel_cities.push_back(hotel->city);
        }
    }
    return hotel_cities;
}
