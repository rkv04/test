#include "registrationwindow.h"
#include "ui_registrationwindow.h"

#include <QMessageBox>
#include <QCryptographicHash>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include "client.h"
#include "appdb.h"
#include "context.h"


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

    QRegularExpression text_exp("^[а-яА-Яa-zA-Z ]*$");
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
    QString phone = this->ui->phoneEdit->text();
    QString name = this->ui->nameEdit->text();
    QString surname = this->ui->surnameEdit->text();
    QString patronymic = this->ui->patronymicEdit->text();
    QByteArray hash_password = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    Client client(phone, hash_password, name, surname, patronymic);

    AppDB *app_db = AppDB::getInstance();
    try {
        app_db->addClient(client);
    }
    catch(const QString& msg) {
        QMessageBox::warning(this, "Tour operator", msg);
        return;
    }
    // catch(const CriticalBd& msg) {
    //     QMessageBox::warning(this, "Tour operator", msg);
    //     qApp->quit();
    // }
    QMessageBox::information(this, "Tour operator", "Вы успешно зарегистрированны");
    emit successfulRegistration();
}

void RegistrationWindow::toLoginWindow() {
    this->author_window = new AuthorizationWindow();
    this->author_window->show();
    this->close();
}
