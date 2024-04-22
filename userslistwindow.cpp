#include "userslistwindow.h"
#include "ui_userslistwindow.h"

UsersListWindow::UsersListWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UsersListWindow)
{
    ui->setupUi(this);
}

UsersListWindow::~UsersListWindow()
{
    delete ui;
}
