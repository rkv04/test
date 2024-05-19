#include "citylistmodel.h"

#include <QVariant>

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
    if (role == CityPtrRole) {
        if (index.row() == 0) {
            return QVariant::fromValue(nullptr);
        }
        return QVariant::fromValue(this->cities.at(index.row() - 1));
    }
    if (role == CityIdRole) {
        if (index.row() == 0) {
            return -1;
        }
        return this->cities.at(index.row() - 1)->id;
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

void CityListModel::addCity(const QSharedPointer<City> &city) {
    this->cities.append(city);
    emit layoutChanged();
}

void CityListModel::addCityIfNotExists(const QSharedPointer<City> &city) {
    for (auto &i : this->cities) {
        if (i->id == city->id) {
            return;
        }
    }
    this->cities.append(city);
}
