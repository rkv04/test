#include "addcitywindow.h"
#include "ui_addcitywindow.h"

#include <QMessageBox>

#include "app.h"

AddCityWindow::AddCityWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddCityWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(App::APPLICATION_NAME);
    connect(this->ui->addButton, SIGNAL(clicked(bool)), this, SLOT(onAddButtonClicked()));
    connect(this->ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

AddCityWindow::~AddCityWindow()
{
    delete ui;
}

void AddCityWindow::onAddButtonClicked() {
    if (!dataIsValid()) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Необходимо заполнить оба поля");
        return;
    }
    this->created_city = QSharedPointer<City>(new City());
    created_city->title = this->ui->titleEdit->text();
    created_city->climate = this->ui->climateEdit->toPlainText();
    AddCityWindow::accept();
}

QSharedPointer<City> AddCityWindow::getCreatedCity() {
    return this->created_city;
}

bool AddCityWindow::dataIsValid() {
    QString title = this->ui->titleEdit->text();
    QString climate = this->ui->climateEdit->toPlainText();
    if (title.isEmpty() || climate.isEmpty()) {
        return false;
    }
    return true;
}
