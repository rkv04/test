#ifndef EMPLOYEEMAINWINDOW_H
#define EMPLOYEEMAINWINDOW_H

#include <QMainWindow>

#include "clientslistwindow.h"
#include "citylistwindow.h"
#include "hotelslistwindow.h"

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

signals:


private:
    Ui::EmployeeMainWindow *ui;
    ClientsListWindow *client_list_window;
    CityListWindow *city_list_window;
    HotelsListWindow *hotel_list_window;
};

#endif // EMPLOYEEMAINWINDOW_H
