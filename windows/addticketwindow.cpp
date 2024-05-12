#include "addticketwindow.h"
#include "ui_addticketwindow.h"

#include <QMessageBox>

#include "app.h"
#include "apperror.h"

AddTicketWindow::AddTicketWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddTicketWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(App::APPLICATION_NAME);
    connect(this->ui->addButton, SIGNAL(clicked(bool)), this, SLOT(onAddButtonClicked()));
    connect(this->ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(this->ui->destinationCityBox, SIGNAL(currentIndexChanged(int)), this, SLOT(destinationCityBoxChanged()));

    this->ui->dateEdit->setDate(QDate::currentDate());
    this->ui->durationBox->addItem("14 дней", 14); // to do
}

AddTicketWindow::~AddTicketWindow()
{
    delete ui;
}

void AddTicketWindow::handleAppError(const AppError &ex) {
    QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
    if (ex.isFatal()) {
        exit(-1);
    }
}

void AddTicketWindow::init() {
    QVector<QSharedPointer<City>> cities;
    QVector<QSharedPointer<Hotel>> hotels;
    App *app = App::getInstance();
    try {
        cities = app->getCityList();
        hotels = app->getHotelList();
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }

    this->city_list_model = QSharedPointer<CityListModel>(new CityListModel());
    this->hotel_list_model = QSharedPointer<HotelListModel>(new HotelListModel());

    this->city_list_model->setCityList(cities);
    this->ui->departureCityBox->setModel(city_list_model.get());
    this->ui->destinationCityBox->setModel(city_list_model.get());
    this->ui->departureCityBox->setMaxVisibleItems(10);
    this->ui->destinationCityBox->setMaxVisibleItems(10);

    this->ui->hotelBox->setModel(hotel_list_model.get());
    this->ui->hotelBox->setMaxVisibleItems(10);

}

void AddTicketWindow::destinationCityBoxChanged() {
    QSharedPointer<City> destination_city = this->ui->destinationCityBox->currentData(CityListModel::CityPtrRole).value<QSharedPointer<City>>();
    if (destination_city == nullptr) {
        this->hotel_list_model->setHotelList(QVector<QSharedPointer<Hotel>>());
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
}

void AddTicketWindow::onAddButtonClicked() {
    QSharedPointer<City> departure_city = this->ui->departureCityBox->currentData(CityListModel::CityPtrRole).value<QSharedPointer<City>>();
    QSharedPointer<Hotel> hotel = this->ui->hotelBox->currentData(HotelListModel::HotelPtrRole).value<QSharedPointer<Hotel>>();
    QString departure_date = this->ui->dateEdit->date().toString("dd.MM.yyyy");
    int duration = this->ui->durationBox->currentData().toInt();
    QString quantity = this->ui->quantityEdit->text();
    QString price = this->ui->priceEdit->text();
    QString travel_time = this->ui->travelTimeEdit->text();
    if (departure_city == nullptr || hotel == nullptr || quantity.isEmpty() || price.isEmpty() || travel_time.isEmpty()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Необходимо заполнить все поля формы");
        return;
    }
    this->created_ticket = QSharedPointer<Ticket>(new Ticket());
    this->created_ticket->price = price.toInt();
    this->created_ticket->duration = duration;
    this->created_ticket->quantity = quantity.toInt();
    this->created_ticket->travel_time = travel_time;
    this->created_ticket->departure_date = departure_date;
    this->created_ticket->departure_city = departure_city;
    this->created_ticket->hotel = hotel;
    AddTicketWindow::accept();
}

QSharedPointer<Ticket> AddTicketWindow::getCreatedTicket() {
    return this->created_ticket;
}
