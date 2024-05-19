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
    void addClientsTicket(const int id_ticket, const int quantity, const int id_client);
    void setQuantityById(const int id_ticket, const int quantity);
    QSharedPointer<Ticket> getTicketById(const int id);
    QVector<QSharedPointer<Ticket>> getTicketList();
    QVector<QSharedPointer<Ticket>> getTicketsAvailableForPurchase();
    QVector<QSharedPointer<Ticket>> getTicketListByFilter(const QMap<QString, QString> &filter);
    QVector<QSharedPointer<Ticket>> getTicketListByListIds(const QStringList &ids);

    QVector<int> getDepartureCitiesIdsFromTickets();
    QVector<int> getDestinationCitiesIdsFromTickets();
    QVector<int> getHotelsIdsFromTickets();
    QVector<int> getHotelsIdsFromTicketsByIdCity(const int id);

private:

    QString textQueryGetAllTickets();
    QString textQueryGetPurchasedTickets();
    QVector<int> getClientTicketsIds();
    QVector<QSharedPointer<Ticket>> getTicketListByQuery(QSqlQuery &query);
    QSharedPointer<Ticket> createTicketByRow(const QSqlRecord &record);
    int getIdLastAddedTicket();

};

#endif // TICKETSERVICE_H
