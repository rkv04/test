#include "addcitywindow.h"
#include "ui_addcitywindow.h"

AddCityWindow::AddCityWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddCityWindow)
{
    ui->setupUi(this);
}

AddCityWindow::~AddCityWindow()
{
    delete ui;
}
