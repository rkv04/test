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
    connect(this->ui->addButton, SIGNAL(clicked(bool)), this, SLOT(onAddButtonClicked()));
    this->ui->durationBox->addItem("14 дней", 14); // to do
}

AddTicketWindow::~AddTicketWindow()
{
    delete ui;
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
        QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }
    this->city_list_model = QSharedPointer<CityListModel>(new CityListModel());
    this->city_list_model->setCityList(cities);
    this->ui->departureCityBox->setModel(city_list_model.get());
    this->ui->destinationCityBox->setModel(city_list_model.get());
    this->ui->departureCityBox->setMaxVisibleItems(10);
    this->ui->destinationCityBox->setMaxVisibleItems(10);

    this->hotel_list_model = QSharedPointer<HotelListModel>(new HotelListModel());
    this->hotel_list_model->setHotelList(hotels);
    this->ui->hotelBox->setModel(hotel_list_model.get());
    this->ui->hotelBox->setMaxVisibleItems(10);

}

void AddTicketWindow::onAddButtonClicked() {
    QSharedPointer<City> departure_city = this->ui->departureCityBox->currentData(Qt::UserRole).value<QSharedPointer<City>>();
    QSharedPointer<City> destination_city = this->ui->destinationCityBox->currentData(Qt::UserRole).value<QSharedPointer<City>>();
    QSharedPointer<Hotel> hotel = this->ui->hotelBox->currentData(Qt::UserRole).value<QSharedPointer<Hotel>>();
    QString departure_date = this->ui->dateEdit->date().toString("dd.MM.yyyy");
    int duration = this->ui->durationBox->currentData().toInt();
    QString quantity = this->ui->quantityEdit->text();
    QString price = this->ui->priceEdit->text();
    QString travel_time = this->ui->travelTimeEdit->text();
    if (departure_city == nullptr || destination_city == nullptr || hotel == nullptr ||
        quantity.isEmpty() || price.isEmpty() || travel_time.isEmpty())
    {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Необходимо заполнить все поля формы");
        return;
    }
    this->created_ticket = QSharedPointer<Ticket>(new Ticket());
    this->created_ticket->price = price.toInt();
    this->created_ticket->duration = duration;
    this->created_ticket->quantity = quantity.toInt();
    this->created_ticket->travel_time = travel_time.toInt();
    this->created_ticket->departure_date = departure_date;
    this->created_ticket->departure_city = departure_city;
    this->created_ticket->hotel = hotel;
    this->created_ticket->hotel->city = destination_city;
    AddTicketWindow::accept();
}

QSharedPointer<Ticket> AddTicketWindow::getCreatedTicket() {
    return this->created_ticket;
}
