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
    connect(this->ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onEditButtonClicked()));
    connect(this->ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(onRowClicked()));
    connect(this->ui->backButton, SIGNAL(clicked(bool)), this, SLOT(onBackButtonClicked()));\
    this->city_table_model = QSharedPointer<CityTableModel>(new CityTableModel());
}

void CityListWindow::handleAppError(const AppError &ex) {
    QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
    if (ex.isFatal()) {
        exit(-1);
    }
}

void CityListWindow::init() {
    this->initModels();
    this->initUi();
}

void CityListWindow::initModels() {
    App *app = App::getInstance();
    QVector<QSharedPointer<City>> city_list;
    try {
        city_list = app->getCityList();
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->city_table_model->setCityList(city_list);
}

void CityListWindow::initUi() {
    this->ui->tableView->setModel(city_table_model.get());
    this->ui->tableView->horizontalHeader()->setStretchLastSection(true);
    this->ui->tableView->resizeColumnsToContents();
    this->ui->tableView->setWordWrap(true); // TO DO
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

CityListWindow::~CityListWindow()
{
    delete ui;
}

void CityListWindow::onAddButtonClicked() {
    AddCityWindow add_city_window;
    add_city_window.setModal(true);
    if (add_city_window.exec() != QDialog::Accepted) {
        return;
    }
    QSharedPointer<City> city = add_city_window.getCreatedCity();
    App *app = App::getInstance();
    try {
        city->id = app->createCity(city);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->city_table_model->addCity(city);
}

bool CityListWindow::confirmDelete() {
    QMessageBox confirm_box;
    confirm_box.setIcon(QMessageBox::Question);
    confirm_box.setWindowTitle(App::APPLICATION_NAME);
    confirm_box.setText("Удалить выбранное?");
    confirm_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);;
    return confirm_box.exec() == QMessageBox::Yes;
}

void CityListWindow::onDeleteButtonClicked() {
    if (!this->tableHasSelection()) {
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
            QSharedPointer<City> city = this->city_table_model->getCityByIndexRow(i.row());
            app->removeCity(city);
            this->city_table_model->removeCityByIndexRow(i.row());
        }
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
}

void CityListWindow::onEditButtonClicked() {
    if (!this->tableHasSelection()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Для редактирования необходимо выделить нужную строку");
        return;
    }
    int selected_row = this->ui->tableView->selectionModel()->selectedRows().first().row();
    QSharedPointer<City> city = this->city_table_model->getCityByIndexRow(selected_row);
    EditCityWindow edit_city_window;
    edit_city_window.setCity(city);
    if (edit_city_window.exec() != EditCityWindow::Accepted) {
        return;
    }
    App *app = App::getInstance();
    try {
        app->updateCity(city);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
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
        this->handleAppError(ex);
        return;
    }
    this->city_table_model->setCityList(cities);
}

void CityListWindow::onRowClicked() {
    int selected_row = this->ui->tableView->selectionModel()->selectedRows().first().row();
    QSharedPointer<City> city = this->city_table_model->getCityByIndexRow(selected_row);
    this->ui->climateEdit->setText(city->climate);
}

bool CityListWindow::tableHasSelection() {
    return this->ui->tableView->selectionModel()->hasSelection();
}

void CityListWindow::onBackButtonClicked() {
    emit showEmployeeMainWindow();
    this->close();
}
