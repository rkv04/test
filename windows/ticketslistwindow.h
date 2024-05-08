#ifndef TICKETSLISTWINDOW_H
#define TICKETSLISTWINDOW_H

#include <QDialog>

#include "tickettablemodel.h"
#include "citylistmodel.h"
#include "hotellistmodel.h"
#include "apperror.h"

namespace Ui {
class TicketsListWindow;
}

class TicketsListWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TicketsListWindow(QWidget *parent = nullptr);
    ~TicketsListWindow();

    void init();

private slots:
    void onAddTicketButtonClicked();
    void showTicketInfo(const QModelIndex &index);

private:
    Ui::TicketsListWindow *ui;
    void handleAppError(const AppError &ex);

    QSharedPointer<TicketTableModel> ticket_table_model;
    QSharedPointer<CityListModel> city_list_model;
    QSharedPointer<HotelListModel> hotel_list_model;
};

#endif // TICKETSLISTWINDOW_H
