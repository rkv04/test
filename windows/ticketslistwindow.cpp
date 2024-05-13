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
    connect(this->ui->deleteTicketButton, SIGNAL(clicked(bool)), this, SLOT(onDeleteButtonClicked()));
    connect(this->ui->findButton, SIGNAL(clicked(bool)), this, SLOT(onFindButtonClicked()));
    connect(this->ui->destinationCityBox, SIGNAL(currentIndexChanged(int)), this, SLOT(destinationCityBoxChanged()));
    connect(this->ui->dateSwitch, SIGNAL(toggled(bool)), this->ui->departureDateEdit, SLOT(setEnabled(bool)));
    connect(this->ui->backButton, SIGNAL(clicked(bool)), this, SLOT(onBackButtonClicked()));
    connect(this->ui->editTicketButton, SIGNAL(clicked(bool)), this, SLOT(onEditButtonClicked()));
    connect(this->ui->ticketView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onEditButtonClicked()));
}

TicketsListWindow::~TicketsListWindow()
{
    delete ui;
}

void TicketsListWindow::initModels() {
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
}

void TicketsListWindow::initUi() {
    this->ui->departureCityBox->setModel(this->city_list_model.get());
    this->ui->destinationCityBox->setModel(this->city_list_model.get());
    this->ui->hotelBox->setModel(this->hotel_list_model.get());
    this->ui->ticketView->setModel(ticket_table_model.get());
    this->ui->departureDateEdit->setDisplayFormat("MMM/yyyy");
    this->ui->departureDateEdit->setDate(QDate::currentDate());
    this->ui->departureDateEdit->setEnabled(false);
    this->ui->departureCityBox->setMaxVisibleItems(10);
    this->ui->destinationCityBox->setMaxVisibleItems(10);
    this->ui->hotelBox->setMaxVisibleItems(10);
    this->ui->ticketView->resizeColumnsToContents();
    this->ui->ticketView->verticalHeader()->stretchLastSection();
    this->ui->ticketView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->priceEditLower->setPlaceholderText("От ...");
    this->ui->priceEditUpper->setPlaceholderText("До ...");
}

void TicketsListWindow::handleAppError(const AppError &ex) {
    QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
    if (ex.isFatal()) {
        exit(-1);
    }
}

bool TicketsListWindow::hasSelection() {
    return this->ui->ticketView->selectionModel()->hasSelection();
}

bool TicketsListWindow::confirmDelete() {
    QMessageBox confirm_box;
    confirm_box.setIcon(QMessageBox::Question);
    confirm_box.setWindowTitle(App::APPLICATION_NAME);
    confirm_box.setText("Удалить выбранное?");
    confirm_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    return confirm_box.exec() == QMessageBox::Yes;
}

void TicketsListWindow::init() {
    this->initModels();
    this->initUi();
}

void TicketsListWindow::destinationCityBoxChanged() {
    QSharedPointer<City> destination_city = this->ui->destinationCityBox->currentData(CityListModel::CityPtrRole).value<QSharedPointer<City>>();
    if (destination_city == nullptr) {
        this->hotel_list_model->setHotelList(QVector<QSharedPointer<Hotel>>());
        this->ui->hotelBox->setEnabled(false);
        return;
    }
    QVector<QSharedPointer<Hotel>> hotels;
    App *app = App::getInstance();
    try {
        hotels = app->getHotelsByCity(destination_city);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->hotel_list_model->setHotelList(hotels);
    this->ui->hotelBox->setEnabled(true);
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

void TicketsListWindow::onEditButtonClicked() {
    if (!this->hasSelection()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Для редактировая необходимо выделить нужную строку");
        return;
    }
    int selected_row = this->ui->ticketView->selectionModel()->selectedRows().first().row();
    QSharedPointer<Ticket> ticket = this->ticket_table_model->getTicketByIndexRow(selected_row);
    EditTicketWindow edit_ticket_window;
    edit_ticket_window.setTicket(ticket);
    edit_ticket_window.init();
    if (edit_ticket_window.exec() != QDialog::Accepted) {
        return;
    }
    QSharedPointer<Ticket> updated_ticket = edit_ticket_window.getUpdatedTicket();
    App *app = App::getInstance();
    try {
        if (updated_ticket->id == -1) {
            updated_ticket->id = app->createTicket(updated_ticket);
            this->ticket_table_model->addTicket(updated_ticket);
        }
        else {
            app->updateTicket(updated_ticket);
        }
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
    }
}

void TicketsListWindow::onDeleteButtonClicked() {
    if (!this->hasSelection()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Для удаления необходимо выделить нужные строки");
        return;
    }
    if (!this->confirmDelete()) {
        return;
    }
    QModelIndexList selected_indexes = this->ui->ticketView->selectionModel()->selectedRows();
    std::sort(selected_indexes.begin(), selected_indexes.end(), [](const QModelIndex &l, const QModelIndex &r){return l.row() > r.row();});
    App *app = App::getInstance();
    try {
        for (auto i : selected_indexes) {
            QSharedPointer<Ticket> ticket = this->ticket_table_model->getTicketByIndexRow(i.row());
            app->removeTicket(ticket);
            this->ticket_table_model->removeTicketByIndexRow(i.row());
        }
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
}

void TicketsListWindow::onFindButtonClicked() {
    QMap<QString, QString> filter = this->createFilter();
    App *app = App::getInstance();
    QVector<QSharedPointer<Ticket>> filtered_tickets;
    try {
        filtered_tickets = app->getTicketListByFilter(filter);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->ticket_table_model->setTicketList(filtered_tickets);
}

QMap<QString, QString> TicketsListWindow::createFilter() {
    QMap<QString, QString> filter;
    auto departure_city = this->ui->departureCityBox->currentData(CityListModel::CityPtrRole).value<QSharedPointer<City>>();
    auto destination_city = this->ui->destinationCityBox->currentData(CityListModel::CityPtrRole).value<QSharedPointer<City>>();
    auto hotel = this->ui->hotelBox->currentData(HotelListModel::HotelPtrRole).value<QSharedPointer<Hotel>>();
    bool dateIsOn = this->ui->dateSwitch->isChecked();
    filter["id_departure_city"] = departure_city == nullptr ? QString() : QString::number(departure_city->id);
    filter["id_destination_city"] = destination_city == nullptr ? QString() : QString::number(destination_city->id);
    filter["id_hotel"] = hotel == nullptr ? QString() : QString::number(hotel->id);
    filter["departure_date"] = dateIsOn ? "%" + this->ui->departureDateEdit->date().toString("MM.yyyy") : "%";
    filter["duration"] = this->ui->durationBox->currentData().toString();
    filter["priceLower"] = this->ui->priceEditLower->text();
    filter["priceUpper"] = this->ui->priceEditUpper->text();
    return filter;
}

void TicketsListWindow::showTicketInfo(const QModelIndex &index) {
    auto ticket = this->ticket_table_model->getTicketByIndexRow(index.row());
    this->ui->climateEdit->setText(ticket->hotel->city->climate);
}

void TicketsListWindow::onBackButtonClicked() {
    emit showEmployeeMainWindow();
    this->close();
}

