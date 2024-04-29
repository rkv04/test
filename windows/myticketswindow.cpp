#include "myticketswindow.h"
#include "ui_myticketswindow.h"

MyTicketsWindow::MyTicketsWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MyTicketsWindow)
{
    ui->setupUi(this);
}

MyTicketsWindow::~MyTicketsWindow()
{
    delete ui;
}
