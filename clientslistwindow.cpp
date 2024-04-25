#include "clientslistwindow.h"
#include "ui_clientslistwindow.h"

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QVariant>

#include "app.h"
#include "apperror.h"
#include "sqlquerymodel.h"

ClientsListWindow::ClientsListWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientsListWindow)
{
    ui->setupUi(this);

    connect(this->ui->findButton, SIGNAL(clicked(bool)), this, SLOT(onFindButtonClicked()));
    connect(this->ui->saveButton, SIGNAL(clicked(bool)), this, SLOT(onSaveButtonClicked()));

    this->init();

}

ClientsListWindow::~ClientsListWindow()
{
    delete ui;
    delete query_model;
}

void ClientsListWindow::init() {
    App *app = App::getInstance();
    QSqlQuery clients_list;
    try {
        clients_list = app->getClientsList();
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, "Tour operator", ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }
    this->query_model = new QSqlQueryModel(this);
    query_model->setQuery(std::move(clients_list));
    this->ui->tableView->setModel(query_model);
    this->ui->tableView->resizeColumnsToContents();
    this->ui->tableView->hideColumn(0);

    this->ui->comboBox->addItem("0%", QVariant(0));
    this->ui->comboBox->addItem("3%", QVariant(3));
    this->ui->comboBox->addItem("5%", QVariant(5));
    this->ui->comboBox->addItem("10%", QVariant(10));
}

void ClientsListWindow::onFindButtonClicked() {
    // QString surname = this->ui->surnameEdit->text();
    // QString name = this->ui->nameEdit->text();
    // QString patronymic = this->ui->patronymicEdit->text();
    // QString phome = this->ui->phoneEdit->text();
    // try {
    //     AppDB *app_db = AppDB::getInstance();
    //     QSqlQuery clients_list = app_db->getClientsByFilter(surname, name, patronymic, phome);
    //     this->query_model->setQuery(clients_list);
    //     this->ui->tableView->setModel(query_model);
    // }
    // catch(const AppError &ex) {
    //     QMessageBox::critical(this, "Tour operator", ex.what());
    //     if (ex.isFatal()) {
    //         exit(-1);
    //     }
    // }
}

void ClientsListWindow::onSaveButtonClicked() {
    QModelIndexList selected_rows = this->ui->tableView->selectionModel()->selectedRows();
    if (selected_rows.isEmpty()) {
        return;
    }
    QModelIndex index = selected_rows.first();
    int client_id = this->ui->tableView->model()->data(index).toInt();
    int discount = this->ui->comboBox->currentData().toInt();

    App *app = App::getInstance();
    try {
        app->setDiscount(client_id, discount);
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, "Tour operator", ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
    }
    this->refreshModel();
}

void ClientsListWindow::refreshModel() {
    App *app = App::getInstance();
    QSqlQuery clients_list;
    try {
        clients_list = app->getClientsList();
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, "Tour operator", ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }
    this->query_model->setQuery(std::move(clients_list));
    this->ui->tableView->repaint();
}
