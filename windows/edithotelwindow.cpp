#include "edithotelwindow.h"
#include "ui_edithotelwindow.h"

EditHotelWindow::EditHotelWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditHotelWindow)
{
    ui->setupUi(this);
}

EditHotelWindow::~EditHotelWindow()
{
    delete ui;
}
