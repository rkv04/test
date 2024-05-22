#include "ticketpurchasewindow.h"
#include "ui_ticketpurchasewindow.h"

#include <QMessageBox>

#include "app.h"
#include "context.h"

TicketPurchaseWindow::TicketPurchaseWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TicketPurchaseWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(App::APPLICATION_NAME);
    connect(this->ui->ticketView, SIGNAL(clicked(QModelIndex)), this, SLOT(showTicketInfo(QModelIndex)));
    connect(this->ui->findButton, SIGNAL(clicked(bool)), this, SLOT(onFindButtonClicked()));
    connect(this->ui->buyButton, SIGNAL(clicked(bool)), this, SLOT(onBuyButtonClicked()));
    connect(this->ui->dateSwitch, SIGNAL(toggled(bool)), this->ui->departureDateEdit, SLOT(setEnabled(bool)));
    connect(this->ui->countEdit, SIGNAL(textChanged(QString)), this, SLOT(setTotalPrice()));
    connect(this->ui->ticketView, SIGNAL(clicked(QModelIndex)), this, SLOT(setTotalPrice()));
    connect(this->ui->backButton, SIGNAL(clicked(bool)), this, SLOT(onCancelButtonClicked()));
    connect(this->ui->resetFiltersButton, SIGNAL(clicked(bool)), this, SLOT(onResetFiltersButtonClicked()));
    connect(this->ui->destinationCityBox, SIGNAL(currentIndexChanged(int)), this, SLOT(destinationCityBoxChanged()));
    this->ticket_table_model = QSharedPointer<TicketTableModel>(new TicketTableModel());
    this->departure_city_list_model = QSharedPointer<CityListModel>(new CityListModel());
    this->destination_city_list_model = QSharedPointer<CityListModel>(new CityListModel());
    this->hotel_list_model = QSharedPointer<HotelListModel>(new HotelListModel());
    this->duration_list_model = QSharedPointer<TicketDurationListModel>(new TicketDurationListModel());
    this->price_validator = QSharedPointer<QIntValidator>(new QIntValidator(0, std::numeric_limits<int>::max()));
}

TicketPurchaseWindow::~TicketPurchaseWindow()
{
    delete ui;
}

void TicketPurchaseWindow::handleAppError(const AppError &ex) {
    if (ex.isFatal()) {
        QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
        exit(-1);
    }
    QMessageBox::warning(this, App::APPLICATION_NAME, ex.what());
}

bool TicketPurchaseWindow::hasSelection() {
    return this->ui->ticketView->selectionModel()->hasSelection();
}

bool TicketPurchaseWindow::confirmPurchase() {
    QMessageBox confirm_box;
    confirm_box.setIcon(QMessageBox::Question);
    confirm_box.setWindowTitle(App::APPLICATION_NAME);
    confirm_box.setText("Подтвердить покупку?");
    confirm_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    return confirm_box.exec() == QMessageBox::Yes;
}

void TicketPurchaseWindow::init() {
    this->initModels();
    this->initUi();
}

void TicketPurchaseWindow::initModels() {
    QVector<QSharedPointer<Ticket>> tickets;
    QVector<QSharedPointer<City>> departure_cities;
    QVector<QSharedPointer<City>> destination_cities;
    QVector<QSharedPointer<Hotel>> hotels;
    App *app = App::getInstance();
    try {
        tickets = app->getTicketsAvailableForPurchase();
        departure_cities = app->getDepartureCitiesFromTickets();
        destination_cities = app->getDestinationCitiesFromTickets();
        hotels = app->getHotelsFromTickets();
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->ticket_table_model->setTicketList(tickets);
    this->departure_city_list_model->setCityList(departure_cities);
    this->destination_city_list_model->setCityList(destination_cities);
    this->hotel_list_model->setHotelList(hotels);
}

void TicketPurchaseWindow::initUi() {
    this->ui->departureCityBox->setModel(this->departure_city_list_model.get());
    this->ui->destinationCityBox->setModel(this->destination_city_list_model.get());
    this->ui->hotelBox->setModel(this->hotel_list_model.get());
    this->ui->durationBox->setModel(this->duration_list_model.get());
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
    this->ui->ticketView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->ui->priceEditLower->setPlaceholderText("От ...");
    this->ui->priceEditUpper->setPlaceholderText("До ...");
    this->ui->priceEditLower->setValidator(this->price_validator.get());
    this->ui->priceEditUpper->setValidator(this->price_validator.get());
}

void TicketPurchaseWindow::showTicketInfo(const QModelIndex &index) {
    auto ticket = this->ticket_table_model->getTicketByIndexRow(index.row());
    this->ui->climateEdit->setText(ticket->hotel->city->climate);
}

void TicketPurchaseWindow::onFindButtonClicked() {
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

QMap<QString, QString> TicketPurchaseWindow::createFilter() {
    QMap<QString, QString> filter;
    auto departure_city = this->ui->departureCityBox->currentData(CityListModel::CityPtrRole).value<QSharedPointer<City>>();
    auto destination_city = this->ui->destinationCityBox->currentData(CityListModel::CityPtrRole).value<QSharedPointer<City>>();
    auto hotel = this->ui->hotelBox->currentData(HotelListModel::HotelPtrRole).value<QSharedPointer<Hotel>>();
    int duration = this->ui->durationBox->currentData(TicketDurationListModel::DurationRole).toInt();
    bool dateIsOn = this->ui->dateSwitch->isChecked();
    filter["id_departure_city"] = departure_city == nullptr ? QString() : QString::number(departure_city->id);
    filter["id_destination_city"] = destination_city == nullptr ? QString() : QString::number(destination_city->id);
    filter["id_hotel"] = hotel == nullptr ? QString() : QString::number(hotel->id);
    filter["departure_date"] = dateIsOn ? "%" + this->ui->departureDateEdit->date().toString("MM.yyyy") : "%";
    filter["duration"] = duration == -1 ? QString() : QString::number(duration);
    filter["priceLower"] = this->ui->priceEditLower->text();
    filter["priceUpper"] = this->ui->priceEditUpper->text();
    filter["quantityIsMoreThen"] = QString::number(0);
    return filter;
}

void TicketPurchaseWindow::onResetFiltersButtonClicked() {
    this->ui->departureCityBox->setCurrentIndex(0);
    this->ui->destinationCityBox->setCurrentIndex(0);
    this->ui->durationBox->setCurrentIndex(0);
    this->ui->dateSwitch->setChecked(false);
    this->ui->priceEditLower->clear();
    this->ui->priceEditUpper->clear();
    App *app = App::getInstance();
    QVector<QSharedPointer<Ticket>> tickets;
    try {
        tickets = app->getTicketsAvailableForPurchase();
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->ticket_table_model->setTicketList(tickets);
}

void TicketPurchaseWindow::destinationCityBoxChanged() {
    auto destination_city = this->ui->destinationCityBox->currentData(CityListModel::CityPtrRole).value<QSharedPointer<City>>();
    if (destination_city == nullptr) {
        this->hotel_list_model->setHotelList(QVector<QSharedPointer<Hotel>>());
        this->ui->hotelBox->setEnabled(false);
        return;
    }
    QVector<QSharedPointer<Hotel>> hotels;
    App *app = App::getInstance();
    try {
        hotels = app->getHotelsFromTicketsByCity(destination_city);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->hotel_list_model->setHotelList(hotels);
    this->ui->hotelBox->setEnabled(true);
}

void TicketPurchaseWindow::onCancelButtonClicked() {
    emit back();
    this->close();
}

void TicketPurchaseWindow::setTotalPrice() {
    if (!this->hasSelection()) {
        return;
    }
    int selected_row = this->ui->ticketView->selectionModel()->selectedRows().first().row();
    auto ticket = this->ticket_table_model->getTicketByIndexRow(selected_row);
    int discount = Context::getContext()->discount;
    int count = this->ui->countEdit->text().toInt();
    int totalPrice = ticket->price * count * (100 - discount) / 100; // TODO
    this->ui->priceLable->setText(QString::number(totalPrice) + " р.");
}

void TicketPurchaseWindow::onBuyButtonClicked() {
    int quantity = this->ui->countEdit->text().toInt();
    if (!this->hasSelection() || quantity == 0) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Для покупки необходимо выделить путёвку и указать количество");
        return;
    }
    if (!this->confirmPurchase()) {
        return;
    }
    int selected_row = this->ui->ticketView->selectionModel()->selectedRows().first().row();
    auto ticket = this->ticket_table_model->getTicketByIndexRow(selected_row);
    App *app = App::getInstance();
    try {
        app->buyTicket(ticket, quantity);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->ticket_table_model->updateQuantityByIndexRow(selected_row, ticket->quantity - quantity);
    QMessageBox::information(this, App::APPLICATION_NAME, "Покупка прошла успешно");
}
