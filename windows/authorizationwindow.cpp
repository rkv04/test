#include "authorizationwindow.h"
#include "ui_authorizationwindow.h"

#include <QMessageBox>

#include "registrationwindow.h"
#include "employeemainwindow.h"
#include "app.h"
#include "apperror.h"


AuthorizationWindow::AuthorizationWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(App::APPLICATION_NAME);
    connect(this->ui->regButton, SIGNAL(clicked(bool)), this, SLOT(regButtonClicked()));
    connect(this->ui->loginButton, SIGNAL(clicked(bool)), this, SLOT(loginButtonClicked()));
}

AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
}

void AuthorizationWindow::regButtonClicked() {
    if (this->registration_window == nullptr) {
        this->registration_window = QSharedPointer<RegistrationWindow>(new RegistrationWindow());
        connect(this->registration_window.get(), SIGNAL(back()), this, SLOT(show()));
    }
    this->registration_window->show();
    this->close();
}

void AuthorizationWindow::loginButtonClicked() {
    QString phone = this->ui->phoneEdit->text();
    QString password = this->ui->passwordEdit->text();

    App *app = App::getInstance();
    QSharedPointer<User> user;

    try {
        user = app->login(phone, password);
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }
    switch (user->role) {
        case 0: {
            if (this->client_main_window == nullptr) {
                this->client_main_window = QSharedPointer<ClientMainWindow>(new ClientMainWindow());
                connect(this->client_main_window.get(), SIGNAL(logout()), this, SLOT(show()));
            }
            this->client_main_window->show();
            this->close();
            break;
        }
        case 1: {
            if (this->employee_main_window == nullptr) {
                this->employee_main_window = QSharedPointer<EmployeeMainWindow>(new EmployeeMainWindow());
                connect(this->employee_main_window.get(), SIGNAL(logout()), this, SLOT(show()));
            }
            this->employee_main_window->show();
            this->close();
            break;
        }
        case 2: {
            if (this->admin_main_window == nullptr) {
                this->admin_main_window = QSharedPointer<AdminMainWindow>(new AdminMainWindow());
                connect(this->admin_main_window.get(), SIGNAL(logout()), this, SLOT(show()));
            }
            this->admin_main_window->show();
            this->close();
            break;
        }
    }
}
