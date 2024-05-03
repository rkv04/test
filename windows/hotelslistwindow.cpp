#include "hotelslistwindow.h"
#include "ui_hotelslistwindow.h"

#include <QMessageBox>

#include "apperror.h"
#include "addhotelwindow.h"
#include "app.h"

HotelsListWindow::HotelsListWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HotelsListWindow)
{
    ui->setupUi(this);
    connect(this->ui->addHotelButton, SIGNAL(clicked(bool)), this, SLOT(onAddHotelButtonClicked()));

    this->ui->tableView->horizontalHeader()->setStretchLastSection(true);
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

HotelsListWindow::~HotelsListWindow()
{
    delete ui;
}

void HotelsListWindow::init() {
    QVector<QSharedPointer<Hotel>> hotels;
    App *app = App::getInstance();
    try {
        hotels = app->getHotelList();
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, "Tour operator", ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }
    this->hotel_model = QSharedPointer<HotelModel>(new HotelModel());
    this->hotel_model->setHotelsList(hotels);
    this->ui->tableView->setModel(hotel_model.get());
}

void HotelsListWindow::onAddHotelButtonClicked() {
    this->add_hotel_window = new AddHotelWindow();

    connect(this->add_hotel_window, SIGNAL(hotelCreated(QSharedPointer<Hotel>)),
            this, SLOT(addHotel(QSharedPointer<Hotel>)));

    this->add_hotel_window->init();
    this->add_hotel_window->setModal(true);
    this->add_hotel_window->exec();
}

void HotelsListWindow::addHotel(const QSharedPointer<Hotel> &hotel) {
    App *app = App::getInstance();
    try {
        hotel->id = app->createHotel(hotel);
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, "Tour operator", ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }
    this->hotel_model->addHotel(hotel);
}
