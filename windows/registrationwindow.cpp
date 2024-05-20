#include "registrationwindow.h"
#include "ui_registrationwindow.h"

#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include "app.h"
#include "apperror.h"


RegistrationWindow::RegistrationWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(App::APPLICATION_NAME);

    connect(this->ui->reg_button, SIGNAL(clicked(bool)), this, SLOT(regButtonClicked()));
    connect(this->ui->sign_in_button, SIGNAL(clicked(bool)), this, SLOT(toLoginWindow()));
    connect(this, SIGNAL(successfulRegistration()), this, SLOT(toLoginWindow()));

    QRegularExpression phone_exp("^\\d{11}$");
    this->phone_validator = QSharedPointer<QValidator>(new QRegularExpressionValidator(phone_exp, this));
    this->ui->phoneEdit->setValidator(phone_validator.get());
    QRegularExpression text_exp("^[а-яА-Яa-zA-Z Ёё]*$");
    this->text_validator = QSharedPointer<QValidator>(new QRegularExpressionValidator(text_exp, this));
    this->ui->nameEdit->setValidator(text_validator.get());
    this->ui->surnameEdit->setValidator(text_validator.get());
    this->ui->patronymicEdit->setValidator(text_validator.get());
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::handleAppError(const AppError &ex) {
    if (ex.isFatal()) {
        QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
        exit(-1);
    }
    QMessageBox::warning(this, App::APPLICATION_NAME, ex.what());
}

void RegistrationWindow::regButtonClicked() {
    if (!this->validateData()) {
        return;
    }
    QSharedPointer<User> client = QSharedPointer<User>(new User());
    client->phone = this->ui->phoneEdit->text();
    client->name = this->ui->nameEdit->text();
    client->surname = this->ui->surnameEdit->text();
    client->patronymic = this->ui->patronymicEdit->text();
    client->password = this->ui->passwordEdit->text();
    try {
        App *app = App::getInstance();
        app->createClient(client);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    QMessageBox::information(this, App::APPLICATION_NAME, "Вы успешно зарегистрированны");
    emit successfulRegistration();
}

void RegistrationWindow::toLoginWindow() {
    emit back();
    this->close();
}

bool RegistrationWindow::validateData() {
    QString surname = this->ui->surnameEdit->text();
    QString name = this->ui->nameEdit->text();
    QString phone = this->ui->phoneEdit->text();
    QString password = this->ui->passwordEdit->text();
    QString password_repeat = this->ui->passwordRepeatEdit->text();
    if (surname.isEmpty() || name.isEmpty() || phone.isEmpty() || password.isEmpty() || password_repeat.isEmpty()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Поля фамилии, имени, номера телефона и пароля должны быть заполнены");
        return false;
    }
    if (password != password_repeat) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Введённые пароли не совпадают");
        return false;
    }
    if (phone.length() < 11) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Номер телефона должен иметь длину 11 знаков (включая код страны)");
        return false;
    }
    return true;
}
