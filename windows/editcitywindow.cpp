#include "editcitywindow.h"
#include "ui_editcitywindow.h"

EditCityWindow::EditCityWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditCityWindow)
{
    ui->setupUi(this);
    connect(this->ui->saveButton, SIGNAL(clicked(bool)), this, SLOT(onSaveButtonClicked()));

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
