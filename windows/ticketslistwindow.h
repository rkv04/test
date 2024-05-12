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

signals:
    void showEmployeeMainWindow();

private slots:
    void onAddTicketButtonClicked();
    void onDeleteButtonClicked();
    void onEditButtonClicked();
    void onFindButtonClicked();
    void onBackButtonClicked();
    void showTicketInfo(const QModelIndex &index);
    void destinationCityBoxChanged();

private:
    Ui::TicketsListWindow *ui;

    void initModels();
    void initUi();
    void handleAppError(const AppError &ex);
    bool hasSelection();
    QMap<QString, QString> createFilter();
    bool confirmDelete();

    QSharedPointer<TicketTableModel> ticket_table_model;
    QSharedPointer<CityListModel> city_list_model;
    QSharedPointer<HotelListModel> hotel_list_model;
};

#endif // TICKETSLISTWINDOW_H
