#ifndef TICKETPURCHASEWINDOW_H
#define TICKETPURCHASEWINDOW_H

#include <QDialog>

#include "apperror.h"
#include "citylistmodel.h"
#include "hotellistmodel.h"
#include "tickettablemodel.h"

namespace Ui {
class TicketPurchaseWindow;
}

class TicketPurchaseWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TicketPurchaseWindow(QWidget *parent = nullptr);
    ~TicketPurchaseWindow();

    void init();

private slots:
    void onFindButtonClicked();
    void onBuyButtonClicked();
    void onCancelButtonClicked();
    void destinationCityBoxChanged();
    void showTicketInfo(const QModelIndex &index);
    void setTotalPrice();

signals:
    void closed();

private:
    Ui::TicketPurchaseWindow *ui;
    void initModels();
    void initUi();
    void handleAppError(const AppError &ex);
    bool hasSelection();
    bool confirmPurchase();
    QMap<QString, QString> createFilter();

    QSharedPointer<TicketTableModel> ticket_table_model;
    QSharedPointer<CityListModel> city_list_model;
    QSharedPointer<HotelListModel> hotel_list_model;
};

#endif // TICKETPURCHASEWINDOW_H
