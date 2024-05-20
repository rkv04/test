#include "authorizationwindow.h"
#include "ui_authorizationwindow.h"

#include <QMessageBox>
#include <QRegularExpression>

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
    QRegularExpression phone_exp("^\\d{11}$");
    this->phone_validator = QSharedPointer<QRegularExpressionValidator>(new QRegularExpressionValidator(phone_exp));
    this->ui->phoneEdit->setValidator(phone_validator.get());
}

AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
}

void AuthorizationWindow::regButtonClicked() {
    if (this->registration_window == nullptr) {
        this->registration_window = QSharedPointer<RegistrationWindow>(new RegistrationWindow());
        connect(this->registration_window.get(), SIGNAL(back()), this, SLOT(clearAndShow()));
    }
    this->registration_window->show();
    this->close();
}

void AuthorizationWindow::clearAndShow() {
    this->ui->phoneEdit->clear();
    this->ui->passwordEdit->clear();
    this->show();
}

bool AuthorizationWindow::validateData() {
    QString phone = this->ui->phoneEdit->text();
    QString password = this->ui->passwordEdit->text();
    if (phone.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Нобходимо заполнить все поля");
        return false;
    }
    // if (phone.length() < 11) {
    //     QMessageBox::warning(this, App::APPLICATION_NAME, "Номер телефона должен иметь длину 11 знаков (включая код страны)");
    //     return false;
    // }
    return true;
}

void AuthorizationWindow::loginButtonClicked() {
    if (!this->validateData()) {
        return;
    }
    QString phone = this->ui->phoneEdit->text();
    QString password = this->ui->passwordEdit->text();
    App *app = App::getInstance();
    QSharedPointer<User> user;
    try {
        user = app->login(phone, password);
    }
    catch(const AppError &ex) {
        if (ex.isFatal()) {
            QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
        }
        QMessageBox::warning(this, App::APPLICATION_NAME, ex.what());
        return;
    }
    switch (user->role) {
        case 0: {
            if (this->client_main_window == nullptr) {
                this->client_main_window = QSharedPointer<ClientMainWindow>(new ClientMainWindow());
                connect(this->client_main_window.get(), SIGNAL(logout()), this, SLOT(clearAndShow()));
            }
            this->client_main_window->show();
            this->close();
            break;
        }
        case 1: {
            if (this->employee_main_window == nullptr) {
                this->employee_main_window = QSharedPointer<EmployeeMainWindow>(new EmployeeMainWindow());
                connect(this->employee_main_window.get(), SIGNAL(logout()), this, SLOT(clearAndShow()));
            }
            this->employee_main_window->show();
            this->close();
            break;
        }
        case 2: {
            if (this->admin_main_window == nullptr) {
                this->admin_main_window = QSharedPointer<AdminMainWindow>(new AdminMainWindow());
                connect(this->admin_main_window.get(), SIGNAL(logout()), this, SLOT(clearAndShow()));
            }
            this->admin_main_window->show();
            this->close();
            break;
        }
    }
}
