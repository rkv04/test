#include "citymodel.h"

CityModel::CityModel(QObject *parent)
    : QAbstractTableModel{parent}
{}

int CityModel::rowCount(const QModelIndex &) const {
    return this->cities.size();
}

int CityModel::columnCount(const QModelIndex &) const {
    return 2;
}

QVariant CityModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        switch(index.column()) {
        case 0:
            return this->cities.at(index.row())->title;
        case 1:
            return this->cities.at(index.row())->climate;
        }
    }
    return QVariant();
}

QVariant CityModel::headerData(int section, Qt::Orientation orientation, int role) const {
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

void CityModel::setCityList(const QVector<QSharedPointer<City>> &cities) {
    this->beginResetModel();
    this->cities = cities;
    this->endResetModel();
}

void CityModel::addCity(const QSharedPointer<City> city) {
    this->cities.append(city);
    emit layoutChanged();
}

QSharedPointer<City> CityModel::getCityByIndexRow(const int row) {
    return this->cities.at(row);
}

void CityModel::removeCityByIndexRow(const int row_index) {
    this->cities.remove(row_index);
    emit layoutChanged();
}

void CityModel::updateCityByIndexRow(const int row, const QSharedPointer<City> updated_city) {
    this->cities.at(row)->title = updated_city->title;
    this->cities.at(row)->climate = updated_city->climate;
    emit layoutChanged();
}