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
    connect(this->ui->findButton, SIGNAL(clicked(bool)), this, SLOT(onFindButtonClicked()));
    connect(this->ui->deleteButton, SIGNAL(clicked(bool)), this, SLOT(onDeleteButtonClicked()));

    this->ui->tableView->horizontalHeader()->setStretchLastSection(true);
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->ui->categoryBox->addItem(QString(), QString());
    this->ui->categoryBox->addItem("Без звёзд", "0");
    this->ui->categoryBox->addItem("1 звезда", "1");
    this->ui->categoryBox->addItem("2 звезды", "2");
    this->ui->categoryBox->addItem("3 звезды", "3");
    this->ui->categoryBox->addItem("4 звезды", "4");
    this->ui->categoryBox->addItem("5 звёзд", "5");
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
        QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }
    this->hotel_table_model = QSharedPointer<HotelTableModel>(new HotelTableModel());
    this->hotel_table_model->setHotelsList(hotels);
    this->ui->tableView->setModel(hotel_table_model.get());
    QVector<QSharedPointer<City>> hotel_cities = this->hotel_table_model->getHotelCities();
    this->city_list_model = QSharedPointer<CityListModel>(new CityListModel());
    this->city_list_model->setCityList(hotel_cities);
    this->ui->cityListBox->setModel(city_list_model.get());
    this->ui->cityListBox->setMaxVisibleItems(10);
}

void HotelsListWindow::refreshCityBox() {
    QVector<QSharedPointer<City>> hotel_cities = this->hotel_table_model->getHotelCities();
    this->city_list_model->setCityList(hotel_cities);
}

void HotelsListWindow::onAddHotelButtonClicked() {
    this->add_hotel_window = new AddHotelWindow();

    connect(this->add_hotel_window, SIGNAL(hotelCreated(QSharedPointer<Hotel>)),
            this, SLOT(addHotel(QSharedPointer<Hotel>)));

    this->add_hotel_window->init();
    this->add_hotel_window->setModal(true);
    this->add_hotel_window->exec();
}

bool HotelsListWindow::confirmDelete() {
    QMessageBox confirm_box;
    confirm_box.setIcon(QMessageBox::Question);
    confirm_box.setWindowTitle(App::APPLICATION_NAME);
    confirm_box.setText("Удалить выбранное?");
    confirm_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);;
    return confirm_box.exec() == QMessageBox::Yes;
}

void HotelsListWindow::onDeleteButtonClicked() {
    QModelIndexList selected_indexes = this->ui->tableView->selectionModel()->selectedRows();
    if (selected_indexes.isEmpty()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Для удаления необходимо выделить нужную строку");
        return;
    }
    if (!confirmDelete()) {
        return;
    }
    int selected_row = selected_indexes.first().row();
    QSharedPointer<Hotel> selected_hotel = this->hotel_table_model->getHotelByIndexRow(selected_row);
    App *app = App::getInstance();
    try {
        app->removeHotel(selected_hotel);
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }
    this->hotel_table_model->removeHotelByIndexRow(selected_row);
    this->refreshCityBox();
}

void HotelsListWindow::addHotel(const QSharedPointer<Hotel> &hotel) {
    App *app = App::getInstance();
    try {
        hotel->id = app->createHotel(hotel);
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }
    this->hotel_table_model->addHotel(hotel);
    this->refreshCityBox();
}

QSharedPointer<City> HotelsListWindow::getCityByCityBoxIndex(const int index) {
    if (index == 0) {
        return nullptr;
    }
    else {
        return this->city_list_model->getCityByIndex(index - 1);
    }
}

void HotelsListWindow::onFindButtonClicked() {
    int city_box_index = this->ui->cityListBox->currentIndex();
    QSharedPointer<City> city = this->getCityByCityBoxIndex(city_box_index);
    QMap<QString, QString> filter;
    filter["title"] = this->ui->titleEdit->text();
    filter["category"] = this->ui->categoryBox->currentData().toString();
    filter["city_id"] = city == nullptr ? QString() : QString::number(city->id);
    App *app = App::getInstance();
    QVector<QSharedPointer<Hotel>> filtered_hotels;
    try {
        filtered_hotels = app->getHotelListByFilter(filter);
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }
    this->hotel_table_model->setHotelsList(filtered_hotels);
}
