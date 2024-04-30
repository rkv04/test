#include "hotelmodel.h"

#include <QVariant>

HotelModel::HotelModel(QObject *parent)
    : QAbstractTableModel{parent}
{}

int HotelModel::rowCount(const QModelIndex &parent) const {
    return this->hotels.size();
}

int HotelModel::columnCount(const QModelIndex &parent) const {
    return 4;
}

QVariant HotelModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        switch(index.column()) {
        case 0:
            return this->hotels.at(index.row())->title;
        case 1:
            return this->hotels.at(index.row())->city_title;
        case 2:
            return this->hotels.at(index.row())->address;
        case 3:
            return this->hotels.at(index.row())->category;
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


void HotelModel::setHotelsList(const QVector<QSharedPointer<Hotel>> hotels) {
    this->beginResetModel();
    this->hotels = hotels;
    this->endResetModel();
}

void HotelModel::addHotel(const QSharedPointer<Hotel> hotel) {
    this->hotels.append(hotel);
    emit layoutChanged();
}

