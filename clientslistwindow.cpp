#include "clientslistwindow.h"
#include "ui_clientslistwindow.h"

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QVariant>

#include "app.h"
#include "apperror.h"

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
    delete client_model;
}

void ClientsListWindow::init() {
    App *app = App::getInstance();
    QVector<QSharedPointer<User>> clients_list;
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
    this->client_model = new ClientModel(this);
    this->client_model->setClientList(clients_list);
    this->ui->tableView->resizeColumnsToContents();
    this->ui->tableView->setModel(client_model);

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
    int client_id = this->client_model->getClientIdByIndexRow(index.row());
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
    this->client_model->refreshDiscountByIndex(index.row(), discount);
    this->ui->tableView->viewport()->update();
}
