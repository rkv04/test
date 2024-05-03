#include "addhotelwindow.h"
#include "ui_addhotelwindow.h"
#include <QMessageBox>

#include "app.h"
#include "apperror.h"
#include "hotel.h"

AddHotelWindow::AddHotelWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddHotelWindow)
{
    ui->setupUi(this);
    connect(this->ui->addButton, SIGNAL(clicked(bool)), this, SLOT(onAddButtonClicked()));
}

AddHotelWindow::~AddHotelWindow()
{
    delete ui;
}

void AddHotelWindow::init() {
    App *app = App::getInstance();
    QVector<QSharedPointer<City>> cities;
    try {
        cities = app->getCityList();
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
    this->ui->cityList->setModel(city_list_model.get());
    this->ui->hotelCategory->addItem("1 звезда", 1);
    this->ui->hotelCategory->addItem("2 звезды", 2);
    this->ui->hotelCategory->addItem("3 звезды", 3);
    this->ui->hotelCategory->addItem("4 звезды", 4);
    this->ui->hotelCategory->addItem("5 звёзд", 5);
}

void AddHotelWindow::onAddButtonClicked() {
    QSharedPointer<Hotel> hotel = QSharedPointer<Hotel>(new Hotel());
    hotel->title = this->ui->titleEdit->text();
    hotel->address = this->ui->addressEdit->text();
    hotel->category = this->ui->hotelCategory->currentData().toInt();
    int city_index = this->ui->cityList->currentIndex();
    hotel->city = this->city_list_model->getCityByIndex(city_index);
    this->close();
    emit hotelCreated(hotel);
}
