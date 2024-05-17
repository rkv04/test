#include "dealservice.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "criticaldb.h"
#include "app.h"

DealService::DealService() {}

void DealService::addDeal(const QSharedPointer<Deal> &deal) {
    QSqlQuery query;
    query.prepare("INSERT INTO Deal (id_ticket, id_client, quantity, date, discount, deal_sum) "
                        "VALUES (?, ?, ?, ?, ?, ?);");
    query.bindValue(0, deal->ticket->id);
    query.bindValue(1, deal->id_client);
    query.bindValue(2, deal->quantity);
    query.bindValue(3, deal->date);
    query.bindValue(4, deal->discount);
    query.bindValue(5, deal->deal_sum);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
}

QVector<QSharedPointer<Deal>> DealService::getDealListByIdClient(const int id) {
    QSqlQuery query;
    QString text_query = "SELECT * FROM Deal WHERE id_client = ?;";
    query.prepare(text_query);
    query.bindValue(0, id);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
    QStringList ids;
    while (query.next()) {
        ids.append(query.value("id_ticket").toString());
    }
    App *app = App::getInstance();
    QVector<QSharedPointer<Ticket>> tickets = app->getTicketListByListIds(ids);
    QMap<int, QSharedPointer<Ticket>> tickets_map;
    for (auto ticket : tickets) {
        tickets_map[ticket->id] = ticket;
    }
    return this->getDealList(query, tickets_map);
}

QVector<QSharedPointer<Deal>> DealService::getDealList(QSqlQuery &query, const QMap<int, QSharedPointer<Ticket>> &tickets) {
    QVector<QSharedPointer<Deal>> deals;
    query.seek(-1);
    while (query.next()) {
        auto ticket = tickets.value(query.value("id_ticket").toInt());
        auto deal = this->createDeal(query.record(), ticket);
        deals.append(deal);
    }
    return deals;
}

QSharedPointer<Deal> DealService::createDeal(const QSqlRecord &record, const QSharedPointer<Ticket> &ticket) {
    auto deal = QSharedPointer<Deal>(new Deal());
    deal->id = record.value("id").toInt();
    deal->id_client = record.value("id_client").toInt();
    deal->id_ticket = record.value("id_ticket").toInt();
    deal->date = record.value("date").toString();
    deal->quantity = record.value("quantity").toInt();
    deal->deal_sum = record.value("deal_sum").toInt();
    deal->discount = record.value("discount").toInt();
    deal->ticket = ticket;
    return deal;
}
