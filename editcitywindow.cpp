#include "editcitywindow.h"
#include "ui_editcitywindow.h"

EditCityWindow::EditCityWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditCityWindow)
{
    ui->setupUi(this);
}

EditCityWindow::~EditCityWindow()
{
    delete ui;
}
