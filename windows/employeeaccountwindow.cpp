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
    this->employee = Context::getContext();
}

void EmployeeAccountWindow::init() {
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
    const QString surname = this->ui->surnameEdit->text();
    const QString name = this->ui->nameEdit->text();
    const QString patronymic = this->ui->patronymicEdit->text();
    const QString phone = this->ui->phoneEdit->text();
    if (surname.isEmpty() || name.isEmpty() || phone.isEmpty()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Поля фамилии, имени и номера телефона должны быть заполнены");
        return;
    }
    this->employee->surname = surname;
    this->employee->name = name;
    this->employee->patronymic = patronymic;
    this->employee->phone = phone;
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

void EmployeeAccountWindow::onChangePasswordButtonClicked() {
    QString password = this->ui->passwordEdit->text();
    QString repeat_password = this->ui->repeatPasswordEdit->text();
    if (password.isEmpty() || repeat_password.isEmpty()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Необходимо заполнить оба поля");
        return;
    }
    if (password != repeat_password) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Введённые пароли не совпадают");
        return;
    }
    App *app = App::getInstance();
    try {
        app->updateEmployeePassword(this->employee->id, password);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    QMessageBox::information(this, App::APPLICATION_NAME, "Пароль успешно изменён");
}
