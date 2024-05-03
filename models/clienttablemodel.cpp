#include "clienttablemodel.h"

ClientTableModel::ClientTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{}

int ClientTableModel::rowCount(const QModelIndex &) const {
    return this->clients.size();
}

int ClientTableModel::columnCount(const QModelIndex &) const {
    return 7;
}

QVariant ClientTableModel::data(const QModelIndex &index, int role) const {
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
                return this->clients.at(index.row())->amount_purchase_tickets;
            case 6:
                return QString::number(this->clients.at(index.row())->discount) + "%";
            }
    }
    return QVariant();
}

QVariant ClientTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
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

void ClientTableModel::setClientList(const QVector<QSharedPointer<User>> &clients) {
    this->beginResetModel();
    this->clients = clients;
    this->endResetModel();
}

int ClientTableModel::getClientIdByIndexRow(int row) {
    return this->clients.at(row)->id;
}

void ClientTableModel::refreshDiscountByIndex(const int row, const int discount) {
    this->clients.at(row)->discount = discount;
    emit layoutChanged();
}
