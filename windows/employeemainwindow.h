#ifndef EMPLOYEEMAINWINDOW_H
#define EMPLOYEEMAINWINDOW_H

#include <QMainWindow>

#include "clientslistwindow.h"
#include "citylistwindow.h"
#include "hotelslistwindow.h"
#include "ticketslistwindow.h"
#include "employeeaccountwindow.h"

namespace Ui {
class EmployeeMainWindow;
}

class EmployeeMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmployeeMainWindow(QWidget *parent = nullptr);
    ~EmployeeMainWindow();

public slots:
    void onClientListButtonClicked();
    void onCityListButtonClicked();
    void onHotelListButtonClicked();
    void onTicketListButtonClicked();
    void onAccountButtonClicked();
    void onLogoutButtonClicked();

signals:
    void logout();

private:
    Ui::EmployeeMainWindow *ui;

    QSharedPointer<ClientsListWindow> client_list_window;
    QSharedPointer<CityListWindow> city_list_window;
    QSharedPointer<HotelsListWindow> hotel_list_window;
    QSharedPointer<TicketsListWindow> ticket_list_window;
    QSharedPointer<EmployeeAccountWindow> employee_account_window;
};

#endif // EMPLOYEEMAINWINDOW_H
