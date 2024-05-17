#ifndef DEALSERVICE_H
#define DEALSERVICE_H

#include <QSharedPointer>
#include <QSqlQuery>

#include "deal.h"

class DealService
{
public:
    DealService();
    void addDeal(const QSharedPointer<Deal> &deal);
    QVector<QSharedPointer<Deal>> getDealListByIdClient(const int id);
private:
    QSharedPointer<Deal> createDeal(const QSqlRecord &record, const QSharedPointer<Ticket> &ticket);
    QVector<QSharedPointer<Deal>> getDealList(QSqlQuery &query, const QMap<int, QSharedPointer<Ticket>> &tickets);
};

#endif // DEALSERVICE_H
