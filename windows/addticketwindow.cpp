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

    this->hotel_list_model = QSharedPointer<HotelListModel>(new HotelListModel());
    this->hotel_list_model->setHotelList(hotels);
    this->ui->hotelBox->setModel(hotel_list_model.get());

}

void AddTicketWindow::onAddButtonClicked() {

}
