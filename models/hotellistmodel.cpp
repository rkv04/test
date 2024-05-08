#include "hotellistmodel.h"

HotelListModel::HotelListModel(QObject *parent)
    : QAbstractListModel{parent}
{}

int HotelListModel::rowCount(const QModelIndex &) const {
    return this->hotels.size() + 1;
}

QVariant HotelListModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        if (index.row() == 0) {
            return QString();
        }
        return this->hotels.at(index.row() - 1)->title;
    }
    if (role == Qt::UserRole) {
        if (index.row() == 0) {
            return QVariant::fromValue(nullptr);
        }
        return QVariant::fromValue(this->hotels.at(index.row() - 1));
    }
    return QVariant();
}

void HotelListModel::setHotelList(const QVector<QSharedPointer<Hotel>> &hotels) {
    this->beginResetModel();
    this->hotels = hotels;
    this->endResetModel();
}
