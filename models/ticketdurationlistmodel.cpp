#include "ticketdurationlistmodel.h"

TicketDurationListModel::TicketDurationListModel(QObject *parent)
    : QAbstractListModel{parent}
{
    this->duration.append(Duration(QString(), -1));
    this->duration.append(Duration("7 дней", 7));
    this->duration.append(Duration("14 дней", 14));
    this->duration.append(Duration("28 дней", 28));
}

int TicketDurationListModel::rowCount(const QModelIndex &) const {
    return this->duration.size();
}

QVariant TicketDurationListModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        return this->duration.at(index.row()).title;
    }
    if (role == DurationRole) {
        return this->duration.at(index.row()).value;
    }
    return QVariant();
}
