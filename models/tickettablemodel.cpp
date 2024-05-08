#include "tickettablemodel.h"

TicketTableModel::TicketTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{}

int TicketTableModel::rowCount(const QModelIndex &parent) const {
    return this->tickets.size();
}

int TicketTableModel::columnCount(const QModelIndex &parent) const {
    return 7;
}

QVariant TicketTableModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        int row = index.row();
        switch (index.column()) {
        case 0:
            return this->tickets.at(row)->departure_city->title;
        case 1:
            return this->tickets.at(row)->hotel->city->title;
        case 2:
            return this->tickets.at(row)->hotel->title;
        case 3:
            return this->tickets.at(row)->departure_date;
        case 4:
            return this->tickets.at(row)->duration;
        case 5:
            return this->tickets.at(row)->price;
        case 6:
            return this->tickets.at(row)->quantity;
        }
    }
    return QVariant();
}

QVariant TicketTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
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

void TicketTableModel::setTicketList(const QVector<QSharedPointer<Ticket>> &tickets) {
    this->beginResetModel();
    this->tickets = tickets;
    this->endResetModel();
}

void TicketTableModel::addTicket(const QSharedPointer<Ticket> &ticket) {
    this->tickets.append(ticket);
    emit layoutChanged();
}

QSharedPointer<Ticket> TicketTableModel::getTicketByIndexRow(const int row) {
    return this->tickets.at(row);
}
