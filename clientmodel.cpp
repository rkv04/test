#include "clientmodel.h"

ClientModel::ClientModel(QObject *parent)
    : QAbstractTableModel{parent}
{}

int ClientModel::rowCount(const QModelIndex &) const {
    return this->clients.size();
}

int ClientModel::columnCount(const QModelIndex &) const {
    return 7;
}

QVariant ClientModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        switch(index.column()) {
            case 0:
                return this->clients.at(index.row())->surname;
            case 1:
                return this->clients.at(index.row())->name;
            case 2:
                return this->clients.at(index.row())->patronymic;
            case 3:
                return this->clients.at(index.row())->phone;
            case 4:
                return this->clients.at(index.row())->address;
            case 5:
                return QString::number(this->clients.at(index.row())->discount) + "%";
            case 6:
                return this->clients.at(index.row())->amount_purchase_tickets;
        }
    }
    return QVariant();
}

QVariant ClientModel::headerData(int section, Qt::Orientation orientation, int role) const {
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

void ClientModel::setClientList(const QVector<QSharedPointer<User>> &clients) {
    this->clients = clients;
}

int ClientModel::getClientIdByIndexRow(int row) {
    return this->clients.at(row)->id;
}

void ClientModel::refreshDiscountByIndex(const int row, const int discount) {
    this->clients.at(row)->discount = discount;
}
