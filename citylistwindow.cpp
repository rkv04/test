#include "citylistwindow.h"
#include "ui_citylistwindow.h"

#include "addcitywindow.h"

CityListWindow::CityListWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CityListWindow)
{
    ui->setupUi(this);

    connect(this->ui->addCityButton, SIGNAL(clicked(bool)), this, SLOT(onAddCityButtonClicked()));
}

CityListWindow::~CityListWindow()
{
    delete ui;
}

void CityListWindow::onAddCityButtonClicked() {
    this->add_city_window = new AddCityWindow();
    this->add_city_window->setModal(true);
    this->add_city_window->exec();
}
