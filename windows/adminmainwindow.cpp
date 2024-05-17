#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"

AdminMainWindow::AdminMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminMainWindow)
{
    ui->setupUi(this);
    connect(this->ui->logoutButton, SIGNAL(clicked(bool)), this, SLOT(onLogoutButtonClicked()));
}

AdminMainWindow::~AdminMainWindow()
{
    delete ui;
}

void AdminMainWindow::onLogoutButtonClicked() {
    emit logout();
    this->close();
}
