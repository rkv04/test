#include "tickettablemodel.h"

TicketTableModel::TicketTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{}

int TicketTableModel::rowCount(const QModelIndex &parent) const {
    return this->tickets.size();
}

int TicketTableModel::columnCount(const QModelIndex &parent) const {
    return 8;
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
            return this->tickets.at(row)->travel_time;
        case 5:
            return QString::number(this->tickets.at(row)->duration) + QString(" дн.");
        case 6:
            return QString::number(this->tickets.at(row)->price) + QString(" руб.");
        case 7:
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

void TicketTableModel::removeTicketByIndexRow(const int row) {
    this->tickets.remove(row);
    emit layoutChanged();
}

void TicketTableModel::updateTicketByIndexRow(const int row, const QSharedPointer<Ticket> &ticket) {
    this->tickets.at(row)->price = ticket->price;
    this->tickets.at(row)->quantity = ticket->quantity;
    this->tickets.at(row)->travel_time = ticket->travel_time;
    this->tickets.at(row)->duration = ticket->duration;
    this->tickets.at(row)->departure_date = ticket->departure_date;
    this->tickets.at(row)->departure_city = ticket->departure_city;
    this->tickets.at(row)->hotel = ticket->hotel;
    emit layoutChanged();
}
