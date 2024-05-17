#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"

AdminMainWindow::AdminMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminMainWindow)
{
    ui->setupUi(this);
    connect(this->ui->logoutButton, SIGNAL(clicked(bool)), this, SLOT(onLogoutButtonClicked()));
    connect(this->ui->employeeButton, SIGNAL(clicked(bool)), this, SLOT(onEmployeeButtonClicked()));
    connect(this->ui->usersButton, SIGNAL(clicked(bool)), this, SLOT(onUsersButtonClicked()));
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
