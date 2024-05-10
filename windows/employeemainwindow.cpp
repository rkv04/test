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
    connect(this->ui->ticketListButton, SIGNAL(clicked(bool)), this, SLOT(onTicketListButtonClicked()));

}

EmployeeMainWindow::~EmployeeMainWindow()
{
    delete ui;
}

void EmployeeMainWindow::onClientListButtonClicked() {
    if (this->client_list_window == nullptr) {
        this->client_list_window = QSharedPointer<ClientsListWindow>(new ClientsListWindow());
        connect(this->client_list_window.get(), SIGNAL(showEmployeeMainWindow()), this, SLOT(show()));
    }
    this->client_list_window->init();
    this->client_list_window->show();
    this->close();
}

void EmployeeMainWindow::onCityListButtonClicked() {
    if (this->city_list_window == nullptr) {
        this->city_list_window = QSharedPointer<CityListWindow>(new CityListWindow());
        connect(this->city_list_window.get(), SIGNAL(showEmployeeMainWindow()), this, SLOT(show()));
    }
    this->city_list_window->init();
    this->city_list_window->show();
    this->close();
}

void EmployeeMainWindow::onHotelListButtonClicked() {
    if (this->hotel_list_window == nullptr) {
        this->hotel_list_window = QSharedPointer<HotelsListWindow>(new HotelsListWindow());
        connect(this->hotel_list_window.get(), SIGNAL(showEmployeeMainWindow()), this, SLOT(show()));
    }
    this->hotel_list_window->init();
    this->hotel_list_window->show();
    this->close();
}

void EmployeeMainWindow::onTicketListButtonClicked() {
    if (this->ticket_list_window == nullptr) {
        this->ticket_list_window = QSharedPointer<TicketsListWindow>(new TicketsListWindow());
        connect(this->ticket_list_window.get(), SIGNAL(showEmployeeMainWindow()), this, SLOT(show()));
    }
    this->ticket_list_window->init();
    this->ticket_list_window->show();
    this->close();
}
