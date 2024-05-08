#include "ticketslistwindow.h"
#include "ui_ticketslistwindow.h"

#include <QMessageBox>

#include "app.h"
#include "apperror.h"
#include "addticketwindow.h"
#include "editticketwindow.h"

TicketsListWindow::TicketsListWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TicketsListWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(App::APPLICATION_NAME);
    connect(this->ui->addTicketButton, SIGNAL(clicked(bool)), this, SLOT(onAddTicketButtonClicked()));
    connect(this->ui->ticketView, SIGNAL(clicked(QModelIndex)), this, SLOT(showTicketInfo(QModelIndex)));
    this->ui->departureCityBox->setMaxVisibleItems(10);
    this->ui->destinationCityBox->setMaxVisibleItems(10);
    this->ui->hotelBox->setMaxVisibleItems(10);
    this->ui->ticketView->resizeColumnsToContents();
    this->ui->ticketView->verticalHeader()->stretchLastSection();
    this->ui->ticketView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

TicketsListWindow::~TicketsListWindow()
{
    delete ui;
}

void TicketsListWindow::handleAppError(const AppError &ex) {
    QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
    if (ex.isFatal()) {
        exit(-1);
    }
}

void TicketsListWindow::init() {

    QVector<QSharedPointer<Ticket>> tickets;
    QVector<QSharedPointer<City>> cities;
    QVector<QSharedPointer<Hotel>> hotels;
    App *app = App::getInstance();
    try {
        tickets = app->getTicketList();
        cities = app->getCityList();
        hotels = app->getHotelList();
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->ticket_table_model = QSharedPointer<TicketTableModel>(new TicketTableModel());
    this->city_list_model = QSharedPointer<CityListModel>(new CityListModel());
    this->hotel_list_model = QSharedPointer<HotelListModel>(new HotelListModel());
    this->ticket_table_model->setTicketList(tickets);
    this->city_list_model->setCityList(cities);
    this->hotel_list_model->setHotelList(hotels);
    this->ui->departureCityBox->setModel(this->city_list_model.get());
    this->ui->destinationCityBox->setModel(this->city_list_model.get());
    this->ui->hotelBox->setModel(this->hotel_list_model.get());
    this->ui->ticketView->setModel(ticket_table_model.get());
}

void TicketsListWindow::onAddTicketButtonClicked() {
    AddTicketWindow add_ticket_window;
    add_ticket_window.init();
    add_ticket_window.setModal(true);
    if (add_ticket_window.exec() != QDialog::Accepted) {
        return;
    }
    QSharedPointer<Ticket> ticket = add_ticket_window.getCreatedTicket();
    App *app = App::getInstance();
    try {
        ticket->id = app->createTicket(ticket);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->ticket_table_model->addTicket(ticket);
}

void TicketsListWindow::showTicketInfo(const QModelIndex &index) {
    auto ticket = this->ticket_table_model->getTicketByIndexRow(index.row());
    this->ui->timeTravelEdit->setText(QString::number(ticket->travel_time));
    this->ui->climateEdit->setText(ticket->hotel->city->climate);
}
