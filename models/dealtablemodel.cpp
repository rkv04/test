#include "dealtablemodel.h"

DealTableModel::DealTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{}

int DealTableModel::rowCount(const QModelIndex &) const {
    return this->deals.size();
}

int DealTableModel::columnCount(const QModelIndex &) const {
    return 10;
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
            return this->deals.at(i)->ticket->duration;
        case 5:
            return this->deals.at(i)->ticket->travel_time;
        case 6:
            return this->deals.at(i)->quantity;
        case 7:
            return QString::number(this->deals.at(i)->deal_sum) + " р.";
        case 8:
            return QString::number(this->deals.at(i)->discount) + "%";
        case 9:
            return this->deals.at(i)->date;
        }
    }
    return QVariant();
}

QVariant DealTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return "Город отпр.";
            case 1:
                return "Город назн.";
            case 2:
                return "Отель";
            case 3:
                return "Дата отпр.";
            case 4:
                return "Длительность";
            case 5:
                return "Время в пути";
            case 6:
                return "Количество";
            case 7:
                return "Сумма покупки";
            case 8:
                return "Скидка";
            case 9:
                return "Дата покупки";
            }
        }
        if (orientation == Qt::Vertical) {
            return QString::number(section);
        }
    }
    return QVariant();
}

void DealTableModel::setDealsList(const QVector<QSharedPointer<Deal>> &deals) {
    this->beginResetModel();
    this->deals = deals;
    this->endResetModel();
}
