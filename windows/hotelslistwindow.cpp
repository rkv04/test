#include "hotelslistwindow.h"
#include "ui_hotelslistwindow.h"

#include "addhotelwindow.h"

HotelsListWindow::HotelsListWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HotelsListWindow)
{
    ui->setupUi(this);
    connect(this->ui->addHotelButton, SIGNAL(clicked(bool)), this, SLOT(onAddHotelButtonClicked()));
}

HotelsListWindow::~HotelsListWindow()
{
    delete ui;
}

void HotelsListWindow::onAddHotelButtonClicked() {
    this->add_hotel_window = new AddHotelWindow();
    this->add_hotel_window->setModal(true);
    this->add_hotel_window->exec();
}
