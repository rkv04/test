#include "userslistwindow.h"
#include "ui_userslistwindow.h"

#include <QMessageBox>

#include "app.h"
#include "apperror.h"

UsersListWindow::UsersListWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UsersListWindow)
{
    ui->setupUi(this);
    connect(this->ui->backButton, SIGNAL(clicked(bool)), this, SLOT(onBackButtonClicked()));
    connect(this->ui->clientRadio, SIGNAL(toggled(bool)), this, SLOT(clientRadioButtonClicked()));
    connect(this->ui->employeeRadio, SIGNAL(toggled(bool)), this, SLOT(employeeRadioButtonClicked()));
}

UsersListWindow::~UsersListWindow()
{
    delete ui;
}

void UsersListWindow::init() {
    this->initModels();
    this->initUi();
}

void UsersListWindow::initUi() {
    this->ui->employeeRadio->setChecked(true);
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableView->resizeColumnsToContents();
    this->ui->tableView->verticalHeader()->stretchLastSection();
}

void UsersListWindow::initModels() {
    QVector<QSharedPointer<User>> clients;
    QVector<QSharedPointer<User>> employees;
    App *app = App::getInstance();
    try {
        clients = app->getClientsList();
        employees = app->getEmployeeList();
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }
    this->client_table_model = QSharedPointer<ClientTableModel>(new ClientTableModel());
    this->client_table_model->setClientList(clients);
    this->employee_table_model = QSharedPointer<EmployeeTableModel>(new EmployeeTableModel());
    this->employee_table_model->setEmployeeList(employees);
}

void UsersListWindow::clientRadioButtonClicked() {
    this->ui->tableView->setModel(this->client_table_model.get());
}

void UsersListWindow::employeeRadioButtonClicked() {
    this->ui->tableView->setModel(this->employee_table_model.get());
}

void UsersListWindow::onBackButtonClicked() {
    emit back();
    this->close();
}


