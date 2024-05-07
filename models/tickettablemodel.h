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

private:

    QVector<QSharedPointer<Ticket>> tickets;
    const QStringList headers = {"Город отпр.", "Город назн.", "Дата отпр.", "Время в пути", "Длительность", "Цена", "Количество"};

};

#endif // TICKETTABLEMODEL_H
