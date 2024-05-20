#include "dealtablemodel.h"

DealTableModel::DealTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{}

int DealTableModel::rowCount(const QModelIndex &) const {
    return this->deals.size();
}

int DealTableModel::columnCount(const QModelIndex &) const {
    return 5;
}

QVariant DealTableModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        int i = index.row();
        switch(index.column()) {
        case 0:
            return this->deals.at(i)->ticket->departure_city->title;
        case 1:
            return this->deals.at(i)->ticket->hotel->city->title;
        case 2:
            return this->deals.at(i)->ticket->hotel->title;
        case 3:
            return this->deals.at(i)->ticket->departure_date;
        case 4:
            return this->deals.at(i)->quantity;
        }
    }
    return QVariant();
}

QVariant DealTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return "Город отправления";
            case 1:
                return "Город назначения";
            case 2:
                return "Отель";
            case 3:
                return "Дата отправления";
            case 4:
                return "Количество";
            }
        }
        if (orientation == Qt::Vertical) {
            return QString::number(section + 1);
        }
    }
    return QVariant();
}

void DealTableModel::setDealsList(const QVector<QSharedPointer<Deal>> &deals) {
    this->beginResetModel();
    this->deals = deals;
    this->endResetModel();
}

QSharedPointer<Deal> DealTableModel::getDealByIndexRow(const int row) {
    return this->deals.at(row);
}
