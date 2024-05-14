#include "editticketwindow.h"
#include "ui_editticketwindow.h"

#include <QMessageBox>

#include "app.h"
#include "apperror.h"

EditTicketWindow::EditTicketWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditTicketWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(App::APPLICATION_NAME);
    connect(this->ui->saveButton, SIGNAL(clicked(bool)), this, SLOT(onSaveButtonClicked()));
    connect(this->ui->destinationCityBox, SIGNAL(currentIndexChanged(int)), this, SLOT(destinationCityBoxChanged()));
    connect(this->ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

EditTicketWindow::~EditTicketWindow()
{
    delete ui;
}

void EditTicketWindow::handleAppError(const AppError &ex) {
    QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
    if (ex.isFatal()) {
        exit(-1);
    }
}

bool EditTicketWindow::saveAsNewTicket() {
    QMessageBox confirm_box;
    confirm_box.setIcon(QMessageBox::Question);
    confirm_box.setWindowTitle(App::APPLICATION_NAME);
    confirm_box.setText("Сохранить путёвку как новую?");
    confirm_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    return confirm_box.exec() == QMessageBox::Yes;
}

void EditTicketWindow::init() {
    this->initModels();
    this->initUi();
}

void EditTicketWindow::setTicket(const QSharedPointer<Ticket> &ticket) {
    this->ticket = ticket;
}

QSharedPointer<Ticket> EditTicketWindow::getUpdatedTicket() {
    return this->ticket;
}

void EditTicketWindow::initModels() {
    QVector<QSharedPointer<City>> cities;
    QVector<QSharedPointer<Hotel>> hotels;
    App *app = App::getInstance();
    try {
        cities = app->getCityList();
        hotels = app->getHotelsByCity(this->ticket->hotel->city);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->city_list_model = QSharedPointer<CityListModel>(new CityListModel());
    this->city_list_model->setCityList(cities);
    this->city_list_model->addCityIfNotExists(this->ticket->departure_city);
    this->city_list_model->addCityIfNotExists(this->ticket->hotel->city);
    this->hotel_list_model = QSharedPointer<HotelListModel>(new HotelListModel());
    this->hotel_list_model->setHotelList(hotels);
}

void EditTicketWindow::initUi() {
    this->ui->hotelBox->setModel(this->hotel_list_model.get());
    this->ui->departureCityBox->setModel(this->city_list_model.get());
    this->ui->destinationCityBox->setModel(this->city_list_model.get());
    this->ui->departureCityBox->setMaxVisibleItems(10);
    this->ui->destinationCityBox->setMaxVisibleItems(10);
    this->ui->hotelBox->setMaxVisibleItems(10);
    this->ui->durationBox->setMaxVisibleItems(10);
    this->ui->durationBox->addItem("14 дней", "14");
    int departure_city_index = this->ui->departureCityBox->findData(this->ticket->departure_city->id, CityListModel::CityIdRole);
    this->ui->departureCityBox->setCurrentIndex(departure_city_index);
    int destination_city_index = this->ui->destinationCityBox->findData(this->ticket->hotel->city->id, CityListModel::CityIdRole);
    this->ui->destinationCityBox->setCurrentIndex(destination_city_index);
    int hotel_index = this->ui->hotelBox->findData(this->ticket->hotel->id, HotelListModel::HotelIdRole);
    this->ui->hotelBox->setCurrentIndex(hotel_index);
    this->ui->departureDateEdit->setDate(QDate::fromString(this->ticket->departure_date, "dd.MM.yyyy"));
    this->ui->travelTimeEdit->setText(this->ticket->travel_time);
    this->ui->quantityEdit->setText(QString::number(this->ticket->quantity));
    this->ui->priceEdit->setText(QString::number(this->ticket->price));
}

void EditTicketWindow::onSaveButtonClicked() {
    auto departure_city = this->ui->departureCityBox->currentData(CityListModel::CityPtrRole).value<QSharedPointer<City>>();
    auto hotel = this->ui->hotelBox->currentData(HotelListModel::HotelPtrRole).value<QSharedPointer<Hotel>>();
    QString departure_date = this->ui->departureDateEdit->date().toString("dd.MM.yyyy");
    QString duration = this->ui->durationBox->currentData().toString(); // to do
    QString travel_time = this->ui->travelTimeEdit->text();
    QString quantity = this->ui->quantityEdit->text();
    QString price = this->ui->priceEdit->text();
    if (departure_city == nullptr || hotel == nullptr || departure_date.isEmpty() || duration.isEmpty() ||
        travel_time.isEmpty() || quantity.isEmpty() || price.isEmpty())
    {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Необходимо заполнить все поля формы");
        return;
    }
    if (this->saveAsNewTicket()) {
        this->ticket = QSharedPointer<Ticket>(new Ticket());
    }
    this->ticket->departure_city = departure_city;
    this->ticket->hotel = hotel;
    this->ticket->departure_date = departure_date;
    this->ticket->duration = duration.toInt();
    this->ticket->travel_time = travel_time;
    this->ticket->quantity = quantity.toInt();
    this->ticket->price = price.toInt();
    QDialog::accept();
}

void EditTicketWindow::destinationCityBoxChanged() {
    auto destination_city = this->ui->destinationCityBox->currentData(CityListModel::CityPtrRole).value<QSharedPointer<City>>();
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
    this->hotel_list_model->addHotelIfNotExists(this->ticket->hotel);
}
