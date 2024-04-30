#include "citylistmodel.h"

CityListModel::CityListModel(QObject *parent)
    : QAbstractListModel{parent}
{}

int CityListModel::rowCount(const QModelIndex &) const {
    return this->cities.size();
}

QVariant CityListModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        return this->cities.at(index.row())->title;
    }
    return QVariant();
}

void CityListModel::setCityList(const QVector<QSharedPointer<City>> &cities) {
    this->beginResetModel();
    this->cities = cities;
    this->endResetModel();
}
