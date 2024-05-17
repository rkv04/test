#include "account.h"
#include "ui_account.h"


#include "context.h"
#include "apperror.h"
#include "app.h"

#include <QMessageBox>

Account::Account(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Account)
{
    ui->setupUi(this);
    this->setWindowTitle(App::APPLICATION_NAME);
    connect(this->ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(onCancelButtonClicked()));
    connect(this->ui->changePasswordButton, SIGNAL(clicked(bool)), this, SLOT(onChangePasswordButtonClicked()));
    connect(this->ui->saveButton, SIGNAL(clicked(bool)), this, SLOT(onSaveButtonClicked()));
}

Account::~Account()
{
    delete ui;
}

void Account::handleAppError(const AppError &ex) {
    if (ex.isFatal()) {
        QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
        exit(-1);
    }
    QMessageBox::warning(this, App::APPLICATION_NAME, ex.what());
}

void Account::onCancelButtonClicked() {
    emit back();
    this->close();
}

void Account::init() {
    this->client = Context::getContext();
    this->ui->nameEdit->setText(this->client->name);
    this->ui->surnameEdit->setText(this->client->surname);
    this->ui->patronymicEdit->setText(this->client->patronymic);
    this->ui->phoneEdit->setText(this->client->phone);
    this->ui->addressEdit->setText(this->client->address);
    this->ui->discountLabel->setText(QString::number(this->client->discount) + "%");
}

void Account::onSaveButtonClicked() {
    const QString surname = this->ui->surnameEdit->text();
    const QString name = this->ui->nameEdit->text();
    const QString patronymic = this->ui->patronymicEdit->text();
    const QString phone = this->ui->phoneEdit->text();
    const QString address = this->ui->addressEdit->text();
    if (surname.isEmpty() || name.isEmpty() || phone.isEmpty()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Поля фамилии, имени и номера телефона должны быть заполнены");
        return;
    }
    this->client->surname = surname;
    this->client->name = name;
    this->client->patronymic = patronymic;
    this->client->phone = phone;
    this->client->address = address;
    App *app = App::getInstance();
    try {
        app->updateCLient(this->client);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    QMessageBox::information(this, App::APPLICATION_NAME, "Данные успешно изменены");
}

void Account::onChangePasswordButtonClicked() {
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
        app->updateUserPassword(this->client, password);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    QMessageBox::information(this, App::APPLICATION_NAME, "Пароль успешно изменён");
}

