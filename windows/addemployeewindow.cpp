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
    QString password = this->ui->passwordEdit->text();
    QString repeatPassword = this->ui->repeatPasswordEdit->text();
    if (password != repeatPassword) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Введённые пароли не совпадают");
        return;
    }
    QString surname = this->ui->surnameEdit->text();
    QString name = this->ui->nameEdit->text();
    QString patronymic = this->ui->patronymicEdit->text();
    QString phone = this->ui->phoneEdit->text();
    if (surname.isEmpty() || name.isEmpty() || phone.isEmpty()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Поля фамилии, имени и номера телефона должны быть заполнены");
        return;
    }
    this->created_employee = QSharedPointer<User>(new User());
    this->created_employee->surname = surname;
    this->created_employee->name = name;
    this->created_employee->patronymic = patronymic;
    this->created_employee->phone = phone;
    this->created_employee->password = password;
    QDialog::accept();
}

QSharedPointer<User> AddEmployeeWindow::getCreatedEmployee() {
    return this->created_employee;
}
