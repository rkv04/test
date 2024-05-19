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
    this->setWindowTitle(App::APPLICATION_NAME);

    connect(this->ui->findButton, SIGNAL(clicked(bool)), this, SLOT(onFindButtonClicked()));
    connect(this->ui->saveButton, SIGNAL(clicked(bool)), this, SLOT(onSaveButtonClicked()));
    connect(this->ui->backButton, SIGNAL(clicked(bool)), this, SLOT(onBackButtonClicked()));
    this->client_model = QSharedPointer<ClientTableModel>(new ClientTableModel());
    this->ui->comboBox->addItem("0%", QVariant(0));
    this->ui->comboBox->addItem("3%", QVariant(3));
    this->ui->comboBox->addItem("5%", QVariant(5));
    this->ui->comboBox->addItem("10%", QVariant(10));
}

void ClientsListWindow::handleAppError(const AppError &ex) {
    QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
    if (ex.isFatal()) {
        exit(-1);
    }
}

void ClientsListWindow::init() {
    this->initModels();
    this->initUi();
}

void ClientsListWindow::initModels() {
    QVector<QSharedPointer<User>> clients_list;
    App *app = App::getInstance();
    try {
        clients_list = app->getClientsList();
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->client_model->setClientList(clients_list);
}

void ClientsListWindow::initUi() {
    this->ui->tableView->setModel(this->client_model.get());
    this->ui->tableView->resizeColumnsToContents();
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

ClientsListWindow::~ClientsListWindow()
{
    delete ui;
}

void ClientsListWindow::onFindButtonClicked() {
    QMap<QString, QString> filter = this->createFilter();
    App *app = App::getInstance();
    QVector<QSharedPointer<User>> clients_list;
    try {
        clients_list = app->getClientsListByFilter(filter);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->client_model->setClientList(clients_list);
}

QMap<QString, QString> ClientsListWindow::createFilter() {
    QMap<QString, QString> filter;
    filter["surname"] = this->ui->surnameEdit->text();
    filter["name"] = this->ui->nameEdit->text();
    filter["patronymic"] = this->ui->patronymicEdit->text();
    filter["phone"] = this->ui->phoneEdit->text();
    return filter;
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
        this->handleAppError(ex);
        return;
    }
    this->client_model->refreshDiscountByIndex(index.row(), discount);
}

void ClientsListWindow::onBackButtonClicked() {
    emit showEmployeeMainWindow();
    this->close();
}
