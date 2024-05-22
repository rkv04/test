#include "addemployeewindow.h"
#include "ui_addemployeewindow.h"

#include <QMessageBox>

#include "app.h"

AddEmployeeWindow::AddEmployeeWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddEmployeeWindow)
{
    ui->setupUi(this);
    connect(this->ui->registrationButton, SIGNAL(clicked(bool)), this, SLOT(onRegistrationButtonClicked()));
    connect(this->ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

AddEmployeeWindow::~AddEmployeeWindow()
{
    delete ui;
}

void AddEmployeeWindow::onRegistrationButtonClicked() {
    if (!this->validateData()) {
        return;
    }
    this->created_employee = QSharedPointer<User>(new User());
    this->created_employee->surname = this->ui->surnameEdit->text();
    this->created_employee->name = this->ui->nameEdit->text();
    this->created_employee->patronymic = this->ui->patronymicEdit->text();
    this->created_employee->phone = this->ui->phoneEdit->text();
    this->created_employee->password = this->ui->passwordEdit->text();
    QDialog::accept();
}

bool AddEmployeeWindow::validateData() {
    QString password = this->ui->passwordEdit->text();
    QString repeatPassword = this->ui->repeatPasswordEdit->text();
    if (password != repeatPassword) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Введённые пароли не совпадают");
        return false;
    }
    QString phone = this->ui->phoneEdit->text();
    if (phone.length() < 11) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Номер телефона должен иметь длину 11 знаков (включая код страны)");
        return false;
    }
    QString surname = this->ui->surnameEdit->text();
    QString name = this->ui->nameEdit->text();
    QString patronymic = this->ui->patronymicEdit->text();
    if (surname.isEmpty() || name.isEmpty() || phone.isEmpty()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Поля фамилии, имени и номера телефона должны быть заполнены");
        return false;
    }
    return true;
}

QSharedPointer<User> AddEmployeeWindow::getCreatedEmployee() {
    return this->created_employee;
}
