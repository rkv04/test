#include "ticketservice.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "criticaldb.h"

TicketService::TicketService() {}

int TicketService::addTicket(const QSharedPointer<Ticket> &ticket) {
    QSqlQuery query;
    query.prepare("INSERT INTO Ticket (price, quantity, id_hotel, id_departure_city, "
                                        "duration, travel_time, departure_date) "
                        "VALUES (?, ?, ?, ?, ?, ?, ?);");
    query.bindValue(0, ticket->price);
    query.bindValue(1, ticket->quantity);
    query.bindValue(2, ticket->hotel->id);
    query.bindValue(3, ticket->departure_city->id);
    query.bindValue(4, ticket->duration);
    query.bindValue(5, ticket->travel_time);
    query.bindValue(6, ticket->departure_date);
    if (!query.exec()) {
        throw CriticalDB(query.lastError().text());
    }
    return this->getIdLastAddedTicket();
}

void TicketService::removeTicketById(const int id) {

}

void TicketService::updateTicket(const QSharedPointer<Ticket> &ticket) {

}

int TicketService::getIdLastAddedTicket() {
    QSqlQuery query;
    QString text_query = "SELECT id FROM Ticket ORDER BY id DESC LIMIT 1;";
    if (!query.exec(text_query)) {
        throw CriticalDB(query.lastError().text());
    }
    query.first();
    return query.value("id").toInt();
}

QVector<QSharedPointer<Ticket>> TicketService::getTicketList() {
    QSqlQuery query;
    QString text_query = "SELECT Ticket.id AS 'id_ticket', "
                                "Ticket.price AS 'price', "
                                "Ticket.quantity AS 'quantity', "
                                "Ticket.duration AS 'duration', "
                                "Ticket.travel_time AS 'travel_time', "
                                "Ticket.id_hotel AS 'id_hotel', "
                                "Ticket.id_departure_city AS 'id_departure_city', "
                                "Ticket.departure_date AS 'departure_date', "
                                "Hotel.title AS 'hotel_title', "
                                "Hotel.id_city AS 'id_destination_city', "
                                "C1.title AS 'city_departure_title', "
                                "C2.title AS 'city_destination_title', "
                                "C2.climate AS 'city_climate' "
                            "FROM Ticket "
                                "JOIN Hotel ON Ticket.id_hotel = Hotel.id "
                                "JOIN City C1 ON Ticket.id_departure_city = C1.id "
                                "JOIN City C2 ON Hotel.id_city = C2.id "
                            "WHERE Ticket.activity_flag = 1 ";
    if (!query.exec(text_query)) {
        throw CriticalDB(query.lastError().text());
    }
    return this->getTicketListByQuery(query);
}

QVector<QSharedPointer<Ticket>> TicketService::getTicketListByQuery(QSqlQuery &query) {
    QVector<QSharedPointer<Ticket>> tickets;
    while (query.next()) {
        auto ticket = this->createTicketByRow(query.record());
        tickets.append(ticket);
    }
    return tickets;
}

QSharedPointer<Ticket> TicketService::createTicketByRow(const QSqlRecord &record) {
    auto ticket = QSharedPointer<Ticket>(new Ticket());
    ticket->hotel = QSharedPointer<Hotel>(new Hotel());
    ticket->hotel->city = QSharedPointer<City>(new City());
    ticket->departure_city = QSharedPointer<City>(new City());
    ticket->id = record.value("id_ticket").toInt();
    ticket->price = record.value("price").toInt();
    ticket->quantity = record.value("quantity").toInt();
    ticket->duration = record.value("duration").toInt();
    ticket->travel_time = record.value("travel_time").toInt();
    ticket->departure_date = record.value("departure_date").toString();
    ticket->departure_city->id = record.value("id_departure_city").toInt();
    ticket->departure_city->title = record.value("city_departure_title").toString();
    ticket->hotel->id = record.value("id_hotel").toInt();
    ticket->hotel->title = record.value("hotel_title").toString();
    ticket->hotel->city->id = record.value("id_destination_city").toInt();
    ticket->hotel->city->title = record.value("city_destination_title").toString();
    ticket->hotel->city->climate = record.value("city_climate").toString();
    return ticket;
}

QVector<QSharedPointer<Ticket>> TicketService::getTicketListByFilter(const QMap<QString, QString> &filter) {

}
