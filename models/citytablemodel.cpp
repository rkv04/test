#include "citytablemodel.h"

CityTableModel::CityTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{}

int CityTableModel::rowCount(const QModelIndex &) const {
    return this->cities.size();
}

int CityTableModel::columnCount(const QModelIndex &) const {
    return 2;
}

QVariant CityTableModel::data(const QModelIndex &index, int role) const {
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

QVariant CityTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
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

void CityTableModel::setCityList(const QVector<QSharedPointer<City>> &cities) {
    this->beginResetModel();
    this->cities = cities;
    this->endResetModel();
}

void CityTableModel::addCity(const QSharedPointer<City> city) {
    this->cities.append(city);
    emit layoutChanged();
}

QSharedPointer<City> CityTableModel::getCityByIndexRow(const int row) {
    return this->cities.at(row);
}

void CityTableModel::removeCityByIndexRow(const int row_index) {
    this->cities.remove(row_index);
    emit layoutChanged();
}

void CityTableModel::updateCityByIndexRow(const int row, const QSharedPointer<City> updated_city) {
    this->cities.at(row)->title = updated_city->title;
    this->cities.at(row)->climate = updated_city->climate;
    emit layoutChanged();
}
