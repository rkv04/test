#include "authorizationwindow.h"
#include "ui_authorizationwindow.h"

#include <QCryptographicHash>
#include <QMessageBox>

#include "registrationwindow.h"
#include "employeemainwindow.h"
#include "appdb.h"
#include "context.h"


AuthorizationWindow::AuthorizationWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);

    try {
        AppDB::init();
    }
    catch(const QString& msg) {
        QMessageBox::critical(this, "Tour operator", msg);
    }

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
    QByteArray hash_password = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    AppDB *db = AppDB::getInstance();
    QPair<int, int> idAndRole;

    try {
        idAndRole = db->login(phone, hash_password);
    }
    catch(const QString& message) {
        QMessageBox::warning(this, "Tour operator", message);
        return;
    }

    switch (idAndRole.second) {
        case 0: {
            Context::setContext(idAndRole.first);
            this->client_main_window = new ClientMainWindow();
            this->client_main_window->show();
            this->close();
            break;
        }
        case 1: {
            Context::setContext(idAndRole.first);
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
