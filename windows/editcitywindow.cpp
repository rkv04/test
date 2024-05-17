#include "editcitywindow.h"
#include "ui_editcitywindow.h"

#include "app.h"

EditCityWindow::EditCityWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditCityWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(App::APPLICATION_NAME);

    connect(this->ui->saveButton, SIGNAL(clicked(bool)), this, SLOT(onSaveButtonClicked()));
    connect(this->ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));

}

EditCityWindow::~EditCityWindow()
{
    delete ui;
}

void EditCityWindow::onSaveButtonClicked() {
    this->city->title = this->ui->titleEdit->text();
    this->city->climate = this->ui->climateEdit->toPlainText();
    EditCityWindow::accept();
}

void EditCityWindow::setCity(const QSharedPointer<City> city) {
    this->city = city;
    this->ui->titleEdit->setText(city->title);
    this->ui->climateEdit->setText(city->climate);
}
