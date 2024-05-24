#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"

#include "app.h"

AdminMainWindow::AdminMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminMainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(App::APPLICATION_NAME);
    connect(this->ui->logoutButton, SIGNAL(clicked(bool)), this, SLOT(onLogoutButtonClicked()));
    connect(this->ui->employeeButton, SIGNAL(clicked(bool)), this, SLOT(onEmployeeButtonClicked()));
    connect(this->ui->usersButton, SIGNAL(clicked(bool)), this, SLOT(onUsersButtonClicked()));
    connect(this->ui->accountButton, SIGNAL(clicked(bool)), this, SLOT(onAccountButtonClicked()));
}

AdminMainWindow::~AdminMainWindow()
{
    delete ui;
}

void AdminMainWindow::onLogoutButtonClicked() {
    emit logout();
    this->close();
}

void AdminMainWindow::onEmployeeButtonClicked() {
    if (this->employee_list_window == nullptr) {
        this->employee_list_window = QSharedPointer<EmployeeListWindow>(new EmployeeListWindow());
        connect(this->employee_list_window.get(), SIGNAL(back()), this, SLOT(show()));
    }
    this->employee_list_window->init();
    this->employee_list_window->show();
    this->close();
}

void AdminMainWindow::onUsersButtonClicked() {
    if (this->user_list_window == nullptr) {
        this->user_list_window = QSharedPointer<UsersListWindow>(new UsersListWindow());
        connect(this->user_list_window.get(), SIGNAL(back()), this, SLOT(show()));
    }
    this->user_list_window->init();
    this->user_list_window->show();
    this->close();
}

void AdminMainWindow::onAccountButtonClicked() {
    if (this->account_window == nullptr) {
        this->account_window = QSharedPointer<EmployeeAccountWindow>(new EmployeeAccountWindow());
        connect(this->account_window.get(), SIGNAL(closed()), this, SLOT(show()));
    }
    this->account_window->init();
    this->account_window->show();
    this->close();
}
