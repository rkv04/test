#include "addhotelwindow.h"
#include "ui_addhotelwindow.h"

#include "app.h"

AddHotelWindow::AddHotelWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddHotelWindow)
{
    ui->setupUi(this);
    App *app = App::getInstance();
    auto cities = app->getCityList();
    this->city_list_model = QSharedPointer<CityListModel>(new CityListModel());
    this->city_list_model->setCityList(cities);
    this->ui->comboBox_3->setModel(city_list_model.get());
}

AddHotelWindow::~AddHotelWindow()
{
    delete ui;
}
