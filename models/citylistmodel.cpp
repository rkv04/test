#include "citylistmodel.h"

CityListModel::CityListModel(QObject *parent)
    : QAbstractListModel{parent}
{}

int CityListModel::rowCount(const QModelIndex &) const {
    return this->cities.size() + 1;
}

QVariant CityListModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        if (index.row() == 0) {
            return QString();
        }
        return this->cities.at(index.row() - 1)->title;
    }
    return QVariant();
}

void CityListModel::setCityList(const QVector<QSharedPointer<City>> &cities) {
    this->beginResetModel();
    this->cities = cities;
    this->endResetModel();
}

QSharedPointer<City> CityListModel::getCityByIndex(const int index) {
    return this->cities.at(index);
}
