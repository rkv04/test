#include "employeemainwindow.h"
#include "ui_employeemainwindow.h"

#include "ticketslistwindow.h"
#include "clientslistwindow.h"
#include "citylistwindow.h"
#include "hotelslistwindow.h"
#include "app.h"

EmployeeMainWindow::EmployeeMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EmployeeMainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(App::APPLICATION_NAME);

    connect(this->ui->clientListButton, SIGNAL(clicked(bool)), this, SLOT(onClientListButtonClicked()));
    connect(this->ui->cityListButton, SIGNAL(clicked(bool)), this, SLOT(onCityListButtonClicked()));
    connect(this->ui->hotelListButton, SIGNAL(clicked(bool)), this, SLOT(onHotelListButtonClicked()));

}

EmployeeMainWindow::~EmployeeMainWindow()
{
    delete ui;
}

void EmployeeMainWindow::onClientListButtonClicked() {
    this->client_list_window = new ClientsListWindow();
    this->client_list_window->show();
    this->close();
}

void EmployeeMainWindow::onCityListButtonClicked() {
    this->city_list_window = new CityListWindow();
    this->city_list_window->show();
    this->close();
}

void EmployeeMainWindow::onHotelListButtonClicked() {
    this->hotel_list_window = new HotelsListWindow();
    this->hotel_list_window->show();
    this->close();
}
