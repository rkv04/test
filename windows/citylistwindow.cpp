#include "citylistwindow.h"
#include "ui_citylistwindow.h"

#include <QMessageBox>

#include "addcitywindow.h"
#include "citytablemodel.h"
#include "app.h"
#include "apperror.h"


CityListWindow::CityListWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CityListWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(App::APPLICATION_NAME);

    connect(this->ui->addCityButton, SIGNAL(clicked(bool)), this, SLOT(onAddButtonClicked()));
    connect(this->ui->deleteCityButton, SIGNAL(clicked(bool)), this, SLOT(onDeleteButtonClicked()));
    connect(this->ui->editCityButton, SIGNAL(clicked(bool)), this, SLOT(onEditButtonClicked()));
    connect(this->ui->findButton, SIGNAL(clicked(bool)), this, SLOT(onFindButtonClicked()));

    this->ui->tableView->horizontalHeader()->setStretchLastSection(true);
    this->ui->tableView->setWordWrap(true);
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void CityListWindow::init() {
    App *app = App::getInstance();
    QVector<QSharedPointer<City>> city_list;
    try {
        city_list = app->getCityList();
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }
    this->city_table_model = QSharedPointer<CityTableModel>(new CityTableModel());
    this->city_table_model->setCityList(city_list);
    this->ui->tableView->setModel(city_table_model.get());
}

CityListWindow::~CityListWindow()
{
    delete ui;
}

void CityListWindow::onAddButtonClicked() {
    this->add_city_window = new AddCityWindow();

    connect(this->add_city_window, SIGNAL(cityCreated(QSharedPointer<City>)),
            this, SLOT(addNewCity(QSharedPointer<City>)));

    this->add_city_window->setModal(true);
    this->add_city_window->exec();
}

void CityListWindow::addNewCity(const QSharedPointer<City> city) {
    App *app = App::getInstance();
    try {
        city->id = app->createCity(city);
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }
    this->city_table_model->addCity(city);
}

void CityListWindow::onDeleteButtonClicked() {
    QModelIndexList selected_indexes = this->ui->tableView->selectionModel()->selectedRows();
    if (selected_indexes.isEmpty()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Для удаления необходимо выделить нужную строку");
        return;
    }
    int selected_row = selected_indexes.first().row();
    QSharedPointer<City> city = this->city_table_model->getCityByIndexRow(selected_row);
    App *app = App::getInstance();
    try {
        app->removeCity(city);
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }
    this->city_table_model->removeCityByIndexRow(selected_row);
}

void CityListWindow::onEditButtonClicked() {
    QModelIndexList selected_indexes = this->ui->tableView->selectionModel()->selectedRows();
    if (selected_indexes.isEmpty()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Для редактирования необходимо выделить нужную строку");
        return;
    }
    int selected_row = selected_indexes.first().row();
    QSharedPointer<City> city = this->city_table_model->getCityByIndexRow(selected_row);
    this->edit_city_window = new EditCityWindow(this);
    this->edit_city_window->setCity(city);
    if (this->edit_city_window->exec() != EditCityWindow::Accepted) {
        return;
    }
    App *app = App::getInstance();
    try {
        app->updateCity(city);
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }
    this->city_table_model->updateCityByIndexRow(selected_row, city);
}

void CityListWindow::onFindButtonClicked() {
    QString title = this->ui->titleEdit->text();
    QVector<QSharedPointer<City>> cities;
    App *app = App::getInstance();
    try {
        cities = app->getCityListByFilter(title);
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
        if (ex.isFatal()) exit(-1);
        return;
    }
    this->city_table_model->setCityList(cities);
}
