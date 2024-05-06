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
    connect(this->ui->editButton, SIGNAL(clicked(bool)), this, SLOT(onEditButtonClicked()));

}

HotelsListWindow::~HotelsListWindow()
{
    delete ui;
}

void HotelsListWindow::init() {
    QVector<QSharedPointer<Hotel>> hotels;
    QVector<QSharedPointer<City>> cities;
    App *app = App::getInstance();
    try {
        hotels = app->getHotelList();
        cities = app->getCityList();
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->hotel_table_model = QSharedPointer<HotelTableModel>(new HotelTableModel());
    this->hotel_table_model->setHotelsList(hotels);
    this->ui->tableView->setModel(hotel_table_model.get());
    this->ui->tableView->horizontalHeader()->setStretchLastSection(true);
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    this->city_list_model = QSharedPointer<CityListModel>(new CityListModel());
    this->city_list_model->setCityList(cities);
    this->ui->cityListBox->setModel(city_list_model.get());
    this->ui->cityListBox->setMaxVisibleItems(10);

    this->category_model = QSharedPointer<HotelCategoryListModel>(new HotelCategoryListModel());
    this->ui->categoryBox->setModel(category_model.get());
    this->ui->categoryBox->setMaxVisibleItems(10);
}

void HotelsListWindow::handleAppError(const AppError &ex) {
    QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
    if (ex.isFatal()) {
        exit(-1);
    }
}

bool HotelsListWindow::hasSelection() {
    return this->ui->tableView->selectionModel()->hasSelection();
}

void HotelsListWindow::onAddHotelButtonClicked() {
    this->add_hotel_window = new AddHotelWindow(this);

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
        this->handleAppError(ex);
        return;
    }
    this->hotel_table_model->addHotel(hotel);
}


bool HotelsListWindow::confirmDelete() {
    QMessageBox confirm_box;
    confirm_box.setIcon(QMessageBox::Question);
    confirm_box.setWindowTitle(App::APPLICATION_NAME);
    confirm_box.setText("Удалить выбранное?");
    confirm_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    return confirm_box.exec() == QMessageBox::Yes;
}

void HotelsListWindow::onDeleteButtonClicked() {
    if (!this->hasSelection()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Для удаления необходимо выделить нужные строки");
        return;
    }
    if (!this->confirmDelete()) {
        return;
    }
    QModelIndexList selected_indexes = this->ui->tableView->selectionModel()->selectedRows();
    std::reverse(selected_indexes.begin(), selected_indexes.end());
    App *app = App::getInstance();
    try {
        for (auto i : selected_indexes) {
            QSharedPointer<Hotel> hotel = this->hotel_table_model->getHotelByIndexRow(i.row());
            app->removeHotel(hotel);
            this->hotel_table_model->removeHotelByIndexRow(i.row());
        }
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
}

void HotelsListWindow::onEditButtonClicked() {
    if (!this->hasSelection()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Для редактирования необходимо выделить нужную строку");
        return;
    }
    int selected_row = this->ui->tableView->selectionModel()->selectedRows().first().row();
    QSharedPointer<Hotel> hotel = this->hotel_table_model->getHotelByIndexRow(selected_row);
    this->edit_hotel_window = new EditHotelWindow(this);
    this->edit_hotel_window->init();
    this->edit_hotel_window->setHotel(hotel);
    if (this->edit_hotel_window->exec() != QDialog::Accepted) {
        return;
    }
    App *app = App::getInstance();
    try {
        app->updateHotel(hotel);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->hotel_table_model->updateHotelByIndexRow(selected_row, hotel);
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
    int category_box_index = this->ui->categoryBox->currentIndex();
    QSharedPointer<City> city = this->getCityByCityBoxIndex(city_box_index);
    QMap<QString, QString> filter;
    filter["title"] = this->ui->titleEdit->text();
    filter["category"] = QString::number(this->category_model->getCategoryByIndex(category_box_index));
    filter["id_city"] = city == nullptr ? QString() : QString::number(city->id);
    App *app = App::getInstance();
    QVector<QSharedPointer<Hotel>> filtered_hotels;
    try {
        filtered_hotels = app->getHotelListByFilter(filter);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->hotel_table_model->setHotelsList(filtered_hotels);
}
