#include "employeeaccountwindow.h"
#include "ui_employeeaccountwindow.h"

#include "context.h"
#include "apperror.h"
#include "app.h"

#include <QMessageBox>

EmployeeAccountWindow::EmployeeAccountWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EmployeeAccountWindow)
{
    ui->setupUi(this);
    connect(this->ui->changePasswordButton, SIGNAL(clicked(bool)), this, SLOT(onChangePasswordButtonClicked()));
    connect(this->ui->saveButton, SIGNAL(clicked(bool)), this, SLOT(onSaveButtonClicked()));
    connect(this->ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(onCancelButtonClicked()));
    QRegularExpression phone_exp("^\\d{11}$");
    this->phone_validator = QSharedPointer<QValidator>(new QRegularExpressionValidator(phone_exp));
    this->ui->phoneEdit->setValidator(phone_validator.get());
}

void EmployeeAccountWindow::init() {
    this->employee = Context::getContext();
    this->ui->surnameEdit->setText(this->employee->surname);
    this->ui->nameEdit->setText(this->employee->name);
    this->ui->patronymicEdit->setText(this->employee->patronymic);
    this->ui->phoneEdit->setText(this->employee->phone);
}

void EmployeeAccountWindow::handleAppError(const AppError &ex) {
    QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
    if (ex.isFatal()) {
        exit(-1);
    }
}

EmployeeAccountWindow::~EmployeeAccountWindow()
{
    delete ui;
}

void EmployeeAccountWindow::onSaveButtonClicked() {
    if (!this->dataIsValid()) {
        return;
    }
    this->employee->surname = this->ui->surnameEdit->text();;
    this->employee->name = this->ui->nameEdit->text();;
    this->employee->patronymic = this->ui->patronymicEdit->text();
    this->employee->phone = this->ui->phoneEdit->text();
    App *app = App::getInstance();
    try {
        app->updateEmployee(this->employee);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    QMessageBox::information(this, App::APPLICATION_NAME, "Данные успешно изменены");
}

bool EmployeeAccountWindow::dataIsValid() {
    QString surname = this->ui->surnameEdit->text();
    QString name = this->ui->nameEdit->text();
    QString phone = this->ui->phoneEdit->text();
    if (surname.isEmpty() || name.isEmpty() || phone.isEmpty()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Поля фамилии, имени и номера телефона должны быть заполнены");
        return false;
    }
    if (phone.length() < 11) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Номер телефона должен иметь длину 11 знаков (включая код страны)");
        return false;
    }
    return true;
}

bool EmployeeAccountWindow::passwordIsValid() {
    QString password = this->ui->passwordEdit->text();
    QString repeat_password = this->ui->repeatPasswordEdit->text();
    if (password.isEmpty() || repeat_password.isEmpty()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Необходимо заполнить оба поля");
        return false;
    }
    if (password != repeat_password) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Введённые пароли не совпадают");
        return false;
    }
    return true;
}

void EmployeeAccountWindow::onChangePasswordButtonClicked() {
    if (!this->passwordIsValid()) {
        return;
    }
    QString password = this->ui->passwordEdit->text();
    App *app = App::getInstance();
    try {
        app->updateUserPassword(this->employee, password);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    QMessageBox::information(this, App::APPLICATION_NAME, "Пароль успешно изменён");
}

void EmployeeAccountWindow::onCancelButtonClicked() {
    emit closed();
    this->close();
}
