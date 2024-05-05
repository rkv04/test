#include "hotellistmodel.h"

HotelListModel::HotelListModel(QObject *parent)
    : QAbstractListModel{parent}
{}

int HotelListModel::rowCount(const QModelIndex &) const {
    return this->hotels.size();
}

QVariant HotelListModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        if (index.row() == 0) {
            return QString();
        }
        return this->hotels.at(index.row())->title;
    }
    return QVariant();
}

void HotelListModel::setHotelList(const QVector<QSharedPointer<Hotel>> &hotels) {
    this->beginResetModel();
    this->hotels = hotels;
    this->endResetModel();
}
