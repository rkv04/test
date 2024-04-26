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
    this->setWindowTitle("Клиенты");

    connect(this->ui->findButton, SIGNAL(clicked(bool)), this, SLOT(onFindButtonClicked()));
    connect(this->ui->saveButton, SIGNAL(clicked(bool)), this, SLOT(onSaveButtonClicked()));

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
    this->ui->tableView->setModel(client_model);

    this->ui->tableView->resizeColumnsToContents();
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    this->ui->comboBox->addItem("0%", QVariant(0));
    this->ui->comboBox->addItem("3%", QVariant(3));
    this->ui->comboBox->addItem("5%", QVariant(5));
    this->ui->comboBox->addItem("10%", QVariant(10));

}

ClientsListWindow::~ClientsListWindow()
{
    delete ui;
    delete client_model;
}

void ClientsListWindow::onFindButtonClicked() {
    QMap<QString, QString> filter;
    filter["surname"] = this->ui->surnameEdit->text();
    filter["name"] = this->ui->nameEdit->text();
    filter["patronymic"] = this->ui->patronymicEdit->text();
    filter["phone"] = this->ui->phoneEdit->text();
    App *app = App::getInstance();
    try {
        auto clients_list = app->getClientsListByFilter(filter);
        this->client_model->setClientList(clients_list);
        this->ui->tableView->repaint();
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, "Tour operator", ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
    }
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