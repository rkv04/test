#include "hotelcategorylistmodel.h"

HotelCategoryListModel::HotelCategoryListModel(QObject *parent)
    : QAbstractListModel{parent}
{
    this->categories.append(Category(QString(), -1));
    this->categories.append(Category("Без звёзд", 0));
    this->categories.append(Category("1 звезда", 1));
    this->categories.append(Category("2 звезды", 2));
    this->categories.append(Category("3 звезды", 3));
    this->categories.append(Category("4 звезды", 4));
    this->categories.append(Category("5 звёзд", 5));
}

int HotelCategoryListModel::rowCount(const QModelIndex &) const {
    return this->categories.size();
}

QVariant HotelCategoryListModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        return this->categories.at(index.row()).title;
    }
    if (role == CategoryRole) {
        return this->categories.at(index.row()).value;
    }
    return QVariant();
}
