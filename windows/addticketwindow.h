#ifndef ADDTICKETWINDOW_H
#define ADDTICKETWINDOW_H

#include <QDialog>
#include <QValidator>

#include "citylistmodel.h"
#include "hotellistmodel.h"
#include "ticketdurationlistmodel.h"
#include "ticket.h"
#include "apperror.h"

namespace Ui {
class AddTicketWindow;
}

class AddTicketWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddTicketWindow(QWidget *parent = nullptr);
    ~AddTicketWindow();

    void init();
    QSharedPointer<Ticket> getCreatedTicket();

private slots:
    void onAddButtonClicked();
    void destinationCityBoxChanged();

private:
    Ui::AddTicketWindow *ui;
    void handleAppError(const AppError &ex);

    QSharedPointer<CityListModel> city_list_model;
    QSharedPointer<HotelListModel> hotel_list_model;
    QSharedPointer<TicketDurationListModel> duration_list_model;
    QSharedPointer<QValidator> number_validator;

    QSharedPointer<Ticket> created_ticket;
};

#endif // ADDTICKETWINDOW_H
