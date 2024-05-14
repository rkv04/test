#include "clientmainwindow.h"
#include "ui_clientmainwindow.h"

ClientMainWindow::ClientMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientMainWindow)
{
    ui->setupUi(this);
    connect(this->ui->accountButton, SIGNAL(clicked(bool)), this, SLOT(onAccountButtonClicked()));
}

ClientMainWindow::~ClientMainWindow()
{
    delete ui;
}

void ClientMainWindow::onAccountButtonClicked() {
    if (this->account_window == nullptr) {
        this->account_window = QSharedPointer<Account>(new Account());
        connect(this->account_window.get(), SIGNAL(closed()), this, SLOT(show()));
    }
    this->account_window->init();
    this->close();
    this->account_window->show();
}

void ClientMainWindow::onTicketsButtonClicked() {

}

void ClientMainWindow::onOffersButtonClicked() {

}
