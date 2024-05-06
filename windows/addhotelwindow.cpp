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
    this->ui->cityList->setMaxVisibleItems(10);

    this->category_model = QSharedPointer<HotelCategoryListModel>(new HotelCategoryListModel());
    this->ui->hotelCategory->setModel(category_model.get());
    this->ui->hotelCategory->setMaxVisibleItems(10);
}

void AddHotelWindow::onAddButtonClicked() {
    int city_box_index = this->ui->cityList->currentIndex();
    QString title = this->ui->titleEdit->text();
    QString address = this->ui->addressEdit->text();
    if (title.isEmpty() || address.isEmpty() || city_box_index == 0) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Необходимо заполнить все поля формы");
        return;
    }
    QSharedPointer<Hotel> hotel = QSharedPointer<Hotel>(new Hotel());
    hotel->title = title;
    hotel->address = address;
    hotel->category = this->ui->hotelCategory->currentData().toInt();
    hotel->city = this->city_list_model->getCityByIndex(city_box_index - 1);
    this->close();
    emit hotelCreated(hotel);
}
