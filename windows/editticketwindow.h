#ifndef EDITTICKETWINDOW_H
#define EDITTICKETWINDOW_H

#include <QDialog>

#include "apperror.h"
#include "ticket.h"
#include "citylistmodel.h"
#include "hotellistmodel.h"
#include "ticketdurationlistmodel.h"

namespace Ui {
class EditTicketWindow;
}

class EditTicketWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditTicketWindow(QWidget *parent = nullptr);
    ~EditTicketWindow();

    QSharedPointer<Ticket> getUpdatedTicket();
    void setTicket(const QSharedPointer<Ticket> &ticket);
    void init();

private slots:
    void onSaveButtonClicked();
    void destinationCityBoxChanged();

private:

    void initModels();
    void initUi();
    void handleAppError(const AppError &ex);
    bool saveAsNewTicket();

    Ui::EditTicketWindow *ui;

    QSharedPointer<Ticket> ticket;
    QSharedPointer<CityListModel> city_list_model;
    QSharedPointer<HotelListModel> hotel_list_model;
    QSharedPointer<TicketDurationListModel> duration_list_model;
};

#endif // EDITTICKETWINDOW_H
