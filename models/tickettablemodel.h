#ifndef TICKETTABLEMODEL_H
#define TICKETTABLEMODEL_H

#include <QAbstractTableModel>

#include "ticket.h"

class TicketTableModel : public QAbstractTableModel
{
public:
    explicit TicketTableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void setTicketList(const QVector<QSharedPointer<Ticket>> &tickets);
    void addTicket(const QSharedPointer<Ticket> &ticket);
    QSharedPointer<Ticket> getTicketByIndexRow(const int row);
    void removeTicketByIndexRow(const int row);
    void updateTicketByIndexRow(const int row, const QSharedPointer<Ticket> &ticket);
    void updateQuantityByIndexRow(const int row, const int quantity);
    void clearModel();

private:
    QVector<QSharedPointer<Ticket>> tickets;
};

#endif // TICKETTABLEMODEL_H
