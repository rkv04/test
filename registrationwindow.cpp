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

    connect(this->ui->reg_button, SIGNAL(clicked(bool)), this, SLOT(regButtonClicked()));
    connect(this->ui->sign_in_button, SIGNAL(clicked(bool)), this, SLOT(toLoginWindow()));
    connect(this, SIGNAL(successfulRegistration()), this, SLOT(toLoginWindow()));


    QRegularExpression phone_exp("^\\d{11}$");
    this->phone_validator = new QRegularExpressionValidator(phone_exp, this);
    this->ui->phoneEdit->setValidator(phone_validator);

    QRegularExpression text_exp("^[а-яА-Яa-zA-Z Ёё]*$");
    this->text_validator = new QRegularExpressionValidator(text_exp, this);
    this->ui->nameEdit->setValidator(text_validator);
    this->ui->surnameEdit->setValidator(text_validator);
    this->ui->patronymicEdit->setValidator(text_validator);
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
    delete phone_validator;
    delete text_validator;
}

void RegistrationWindow::regButtonClicked() {
    QString password = this->ui->passwordEdit->text();
    QString password_repeat = this->ui->passwordRepeatEdit->text();
    if (password != password_repeat) {
        QMessageBox::warning(this, "Tour operator", "Введённые пароли не совпадают");
        return;
    }
    User client;
    client.phone = this->ui->phoneEdit->text();
    client.name = this->ui->nameEdit->text();
    client.surname = this->ui->surnameEdit->text();
    client.patronymic = this->ui->patronymicEdit->text();
    client.password = password;

    try {
        App *app = App::getInstance();
        app->createClient(client);
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, "Tour operator", ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }

    QMessageBox::information(this, "Tour operator", "Вы успешно зарегистрированны");
    emit successfulRegistration();
}

void RegistrationWindow::toLoginWindow() {
    this->author_window = new AuthorizationWindow();
    this->author_window->show();
    this->close();
}
