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
    this->setWindowTitle(App::APPLICATION_NAME);
    connect(this->ui->addHotelButton, SIGNAL(clicked(bool)), this, SLOT(onAddHotelButtonClicked()));
    connect(this->ui->findButton, SIGNAL(clicked(bool)), this, SLOT(onFindButtonClicked()));
    connect(this->ui->deleteButton, SIGNAL(clicked(bool)), this, SLOT(onDeleteButtonClicked()));
    connect(this->ui->editButton, SIGNAL(clicked(bool)), this, SLOT(onEditButtonClicked()));
    connect(this->ui->backButton, SIGNAL(clicked(bool)), this, SLOT(onBackButtonClicked()));
    connect(this->ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onEditButtonClicked()));
    connect(this->ui->resetFiltersButton, SIGNAL(clicked(bool)), this, SLOT(onResetFiltersButtonClicked()));
    this->city_list_model = QSharedPointer<CityListModel>(new CityListModel());
    this->category_model = QSharedPointer<HotelCategoryListModel>(new HotelCategoryListModel());
    this->hotel_table_model = QSharedPointer<HotelTableModel>(new HotelTableModel());
}

HotelsListWindow::~HotelsListWindow()
{
    delete ui;
}

void HotelsListWindow::init() {
    this->initModels();
    this->initUi();
}

void HotelsListWindow::initModels() {
    QVector<QSharedPointer<Hotel>> hotels;
    QVector<QSharedPointer<City>> cities;
    App *app = App::getInstance();
    try {
        hotels = app->getHotelList();
        cities = app->getCitiesFromHotels();
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->hotel_table_model->setHotelsList(hotels);
    this->city_list_model->setCityList(cities);
}

void HotelsListWindow::initUi() {
    this->ui->tableView->setModel(hotel_table_model.get());
    this->ui->cityListBox->setModel(city_list_model.get());
    this->ui->categoryBox->setModel(category_model.get());
    this->ui->tableView->resizeColumnsToContents();
    this->ui->tableView->horizontalHeader()->setStretchLastSection(true);
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->cityListBox->setMaxVisibleItems(10);
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
    AddHotelWindow add_hotel_window;
    add_hotel_window.init();
    add_hotel_window.setModal(true);
    if (add_hotel_window.exec() != QDialog::Accepted) {
        return;
    }
    auto hotel = add_hotel_window.getCreatedHotel();
    App *app = App::getInstance();
    try {
        hotel->id = app->createHotel(hotel);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->hotel_table_model->addHotel(hotel);
    this->city_list_model->addCity(hotel->city);
    this->ui->tableView->resizeColumnsToContents();
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
    std::sort(selected_indexes.begin(), selected_indexes.end(), [](const QModelIndex &l, const QModelIndex &r){return l.row() > r.row();});
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
    }
}

void HotelsListWindow::onEditButtonClicked() {
    if (!this->hasSelection()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Для редактирования необходимо выделить нужную строку");
        return;
    }
    int selected_row = this->ui->tableView->selectionModel()->selectedRows().first().row();
    QSharedPointer<Hotel> hotel = this->hotel_table_model->getHotelByIndexRow(selected_row);
    EditHotelWindow edit_hotel_window;
    edit_hotel_window.init();
    edit_hotel_window.setHotel(hotel);
    if (edit_hotel_window.exec() != QDialog::Accepted) {
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

void HotelsListWindow::onFindButtonClicked() {
    QMap<QString, QString> filter = this->createFilter();
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

void HotelsListWindow::onBackButtonClicked() {
    emit showEmployeeMainWindow();
    this->close();
}

void HotelsListWindow::onResetFiltersButtonClicked() {
    this->ui->titleEdit->clear();
    this->ui->cityListBox->setCurrentIndex(0);
    this->ui->categoryBox->setCurrentIndex(0);
    App *app = App::getInstance();
    QVector<QSharedPointer<Hotel>> hotels;
    try {
        hotels = app->getHotelList();
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->hotel_table_model->setHotelsList(hotels);
}

QMap<QString, QString> HotelsListWindow::createFilter() {
    QMap<QString, QString> filter;
    QSharedPointer<City> city = this->ui->cityListBox->currentData(Qt::UserRole).value<QSharedPointer<City>>();\
    int category = this->ui->categoryBox->currentData(HotelCategoryListModel::CategoryRole).toInt();
    filter["title"] = this->ui->titleEdit->text() + "%";
    filter["category"] = category == -1 ? QString() : QString::number(category);
    filter["id_city"] = city == nullptr ? QString() : QString::number(city->id);
    return filter;
}
