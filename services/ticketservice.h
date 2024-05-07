#ifndef TICKETSERVICE_H
#define TICKETSERVICE_H

#include "ticket.h"

#include <QSqlQuery>

class TicketService
{
public:
    TicketService();

    int addTicket(const QSharedPointer<Ticket> &ticket);
    void removeTicketById(const int id);
    void updateTicket(const QSharedPointer<Ticket> &ticket);
    QVector<QSharedPointer<Ticket>> getTicketList();
    QVector<QSharedPointer<Ticket>> getTicketListByFilter(const QMap<QString, QString> &filter);

private:

    QVector<QSharedPointer<Ticket>> getTicketListByQuery(QSqlQuery &query);
    QSharedPointer<Ticket> createTicketByRow(const QSqlRecord &record);
    int getIdLastAddedTicket();

};

#endif // TICKETSERVICE_H
