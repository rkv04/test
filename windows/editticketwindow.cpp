#include "editticketwindow.h"
#include "ui_editticketwindow.h"

EditTicketWindow::EditTicketWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditTicketWindow)
{
    ui->setupUi(this);
}

EditTicketWindow::~EditTicketWindow()
{
    delete ui;
}
