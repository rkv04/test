#ifndef DEAL_H
#define DEAL_H

#include <QSharedPointer>

#include "ticket.h"
#include "user.h"

class Deal
{
public:
    Deal();
    int id;
    int id_ticket;
    QSharedPointer<Ticket> ticket;
    int id_client;
    int quantity;
    QString date;
    int discount;
    int deal_sum;
};

#endif // DEAL_H
