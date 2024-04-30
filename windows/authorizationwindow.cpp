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
    this->reg_window = new RegistrationWindow();
    this->reg_window->show();
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
            this->client_main_window = new ClientMainWindow();
            this->client_main_window->show();
            this->close();
            break;
        }
        case 1: {
            this->employee_main_window = new EmployeeMainWindow();
            this->employee_main_window->show();
            this->close();
            break;
        }
        case 2: {
            QMessageBox::information(this, "Tour operator", "Это администратор");
            break;
        }

    }
}
