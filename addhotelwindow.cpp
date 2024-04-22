#include "addhotelwindow.h"
#include "ui_addhotelwindow.h"

AddHotelWindow::AddHotelWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddHotelWindow)
{
    ui->setupUi(this);
}

AddHotelWindow::~AddHotelWindow()
{
    delete ui;
}
