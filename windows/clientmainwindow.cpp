#include "clientmainwindow.h"
#include "ui_clientmainwindow.h"

#include "app.h"

ClientMainWindow::ClientMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientMainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(App::APPLICATION_NAME);
    connect(this->ui->accountButton, SIGNAL(clicked(bool)), this, SLOT(onAccountButtonClicked()));
    connect(this->ui->offersButton, SIGNAL(clicked(bool)), this, SLOT(onOffersButtonClicked()));
    connect(this->ui->ticketsButton, SIGNAL(clicked(bool)), this, SLOT(onTicketsButtonClicked()));
    connect(this->ui->logoutButton, SIGNAL(clicked(bool)), this, SLOT(onLogoutButtonClicked()));
}

ClientMainWindow::~ClientMainWindow()
{
    delete ui;
}

void ClientMainWindow::onAccountButtonClicked() {
    if (this->account_window == nullptr) {
        this->account_window = QSharedPointer<Account>(new Account());
        connect(this->account_window.get(), SIGNAL(back()), this, SLOT(show()));
    }
    this->account_window->init();
    this->account_window->show();
    this->close();
}

void ClientMainWindow::onTicketsButtonClicked() {
    if (this->client_ticket_window == nullptr) {
        this->client_ticket_window = QSharedPointer<ClientTicketsWindow>(new ClientTicketsWindow());
        connect(this->client_ticket_window.get(), SIGNAL(back()), this, SLOT(show()));
    }
    this->client_ticket_window->init();
    this->client_ticket_window->show();
    this->close();
}

void ClientMainWindow::onOffersButtonClicked() {
    if (this->ticket_purchase_window == nullptr) {
        this->ticket_purchase_window = QSharedPointer<TicketPurchaseWindow>(new TicketPurchaseWindow());
        connect(this->ticket_purchase_window.get(), SIGNAL(back()), this, SLOT(show()));
    }
    this->ticket_purchase_window->init();
    this->ticket_purchase_window->show();
    this->close();
}

void ClientMainWindow::onLogoutButtonClicked() {
    emit logout();
    this->close();
}
