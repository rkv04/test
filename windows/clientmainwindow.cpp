#include "clientmainwindow.h"
#include "ui_clientmainwindow.h"

ClientMainWindow::ClientMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientMainWindow)
{
    ui->setupUi(this);
    connect(this->ui->accountButton, SIGNAL(clicked(bool)), this, SLOT(onAccountButtonClicked()));
    connect(this->ui->offersButton, SIGNAL(clicked(bool)), this, SLOT(onOffersButtonClicked()));
    connect(this->ui->ticketsButton, SIGNAL(clicked(bool)), this, SLOT(onTicketsButtonClicked()));
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
    if (this->client_ticket_window == nullptr) {
        this->client_ticket_window = QSharedPointer<ClientTicketsWindow>(new ClientTicketsWindow());
    }
    this->client_ticket_window->init();
    this->close();
    this->client_ticket_window->show();
}

void ClientMainWindow::onOffersButtonClicked() {
    if (this->ticket_purchase_window == nullptr) {
        this->ticket_purchase_window = QSharedPointer<TicketPurchaseWindow>(new TicketPurchaseWindow());
    }
    this->ticket_purchase_window->init();
    this->close();
    this->ticket_purchase_window->show();
}
