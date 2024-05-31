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
    QRegularExpression phone_exp("^\\d{11}$");
    this->phone_validator = QSharedPointer<QRegularExpressionValidator>(new QRegularExpressionValidator(phone_exp));
    this->ui->phoneEdit->setValidator(phone_validator.get());
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
    this->ui->passwordEdit->clear();
    this->ui->repeatPasswordEdit->clear();
}

void Account::onSaveButtonClicked() {
    if (!this->dataIsValid()) {
        return;
    }
    this->client->surname = this->ui->surnameEdit->text();
    this->client->name = this->ui->nameEdit->text();
    this->client->patronymic = this->ui->patronymicEdit->text();
    this->client->phone = this->ui->phoneEdit->text();
    this->client->address = this->ui->addressEdit->text();
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
    if (!this->passwordIsValid()) {
        return;
    }
    QString password = this->ui->passwordEdit->text();
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

bool Account::passwordIsValid() {
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

bool Account::dataIsValid() {
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
