#include "addticketwindow.h"
#include "ui_addticketwindow.h"

AddTicketWindow::AddTicketWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddTicketWindow)
{
    ui->setupUi(this);
}

AddTicketWindow::~AddTicketWindow()
{
    delete ui;
}
