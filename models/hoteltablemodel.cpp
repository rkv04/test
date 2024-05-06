#include "hoteltablemodel.h"

#include <QVariant>

HotelTableModel::HotelTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{}

int HotelTableModel::rowCount(const QModelIndex &) const {
    return this->hotels.size();
}

int HotelTableModel::columnCount(const QModelIndex &) const {
    return 4;
}

QVariant HotelTableModel::data(const QModelIndex &index, int role) const {
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

QVariant HotelTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
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


void HotelTableModel::setHotelsList(const QVector<QSharedPointer<Hotel>> &hotels) {
    this->beginResetModel();
    this->hotels = hotels;
    this->endResetModel();
}

void HotelTableModel::addHotel(const QSharedPointer<Hotel> &hotel) {
    this->hotels.append(hotel);
    emit layoutChanged();
}

QVector<QSharedPointer<City>> HotelTableModel::getHotelCities() {
    QSet<QString> unique_city_title;
    QVector<QSharedPointer<City>> hotel_cities;
    for (auto hotel : this->hotels) {
        if (!unique_city_title.contains(hotel->city->title)) {
            unique_city_title.insert(hotel->city->title);
            hotel_cities.push_back(hotel->city);
        }
    }
    std::sort(hotel_cities.begin(), hotel_cities.end(), [] (QSharedPointer<City> &l_city, QSharedPointer<City> &r_city) {
        return l_city->title < r_city->title;
    });
    return hotel_cities;
}

void HotelTableModel::removeHotelByIndexRow(const int row) {
    this->hotels.remove(row);
    emit layoutChanged();
}

void HotelTableModel::updateHotelByIndexRow(const int row, const QSharedPointer<Hotel> &updated_hotel) {
    this->hotels.at(row)->title = updated_hotel->title;
    this->hotels.at(row)->category = updated_hotel->category;
    this->hotels.at(row)->address = updated_hotel->address;
    this->hotels.at(row)->city = updated_hotel->city;
    emit layoutChanged();
}

QSharedPointer<Hotel> HotelTableModel::getHotelByIndexRow(const int row) {
    return this->hotels.at(row);
}
