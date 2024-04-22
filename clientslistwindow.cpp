#include "clientslistwindow.h"
#include "ui_clientslistwindow.h"

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>

#include "appdb.h"

ClientsListWindow::ClientsListWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientsListWindow)
{
    ui->setupUi(this);

    connect(this->ui->findButton, SIGNAL(clicked(bool)), this, SLOT(onFindButtonClicked()));

    this->init();

}

ClientsListWindow::~ClientsListWindow()
{
    delete ui;
}

void ClientsListWindow::init() {
    AppDB *app_db = AppDB::getInstance();
    QSqlQuery clients_list;
    try {
        clients_list = app_db->getAllClients();
    }
    catch(const QString& msg) {

    }
    this->query_model = new QSqlQueryModel(this);
    query_model->setQuery(clients_list);
    this->ui->tableView->setModel(query_model);
    this->ui->tableView->resizeColumnsToContents();
}

void ClientsListWindow::onFindButtonClicked() {
    QString surname = this->ui->surnameEdit->text();
    QString name = this->ui->nameEdit->text();
    QString patronymic = this->ui->patronymicEdit->text();
    QString phome = this->ui->phoneEdit->text();
    try {
        AppDB *app_db = AppDB::getInstance();
        QSqlQuery clients_list = app_db->getClientsByFilter(surname, name, patronymic, phome);
        this->query_model->setQuery(clients_list);
        this->ui->tableView->setModel(query_model);
    }
    catch(const QString& msg) {
        QMessageBox::critical(this, "Tour operator", msg);
    }
}
