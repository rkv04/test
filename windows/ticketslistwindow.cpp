#include "ticketslistwindow.h"
#include "ui_ticketslistwindow.h"

#include <QMessageBox>

#include "app.h"
#include "apperror.h"

TicketsListWindow::TicketsListWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TicketsListWindow)
{
    ui->setupUi(this);
    connect(this->ui->addTicketButton, SIGNAL(clicked(bool)), this, SLOT(onAddTicketButtonClicked()));
}

TicketsListWindow::~TicketsListWindow()
{
    delete ui;
}

void TicketsListWindow::handleAppError(const AppError &ex) {
    QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
    if (ex.isFatal()) {
        exit(-1);
    }
}

void TicketsListWindow::init() {

    QVector<QSharedPointer<Ticket>> tickets;
    App *app = App::getInstance();
    try {
        tickets = app->getTicketList();
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }

    this->ticket_table_model = QSharedPointer<TicketTableModel>(new TicketTableModel());
    this->ticket_table_model->setTicketList(tickets);
    this->ui->ticketView->resizeColumnsToContents();
    this->ui->ticketView->verticalHeader()->stretchLastSection();
    this->ui->ticketView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->ticketView->setModel(ticket_table_model.get());
}

void TicketsListWindow::onAddTicketButtonClicked() {
    AddTicketWindow add_ticket_window;
    add_ticket_window.init();
    add_ticket_window.setModal(true);
    if (add_ticket_window.exec() != QDialog::Accepted) {
        return;
    }
    QSharedPointer<Ticket> ticket = add_ticket_window.getCreatedTicket();
    App *app = App::getInstance();
    try {
        ticket->id = app->createTicket(ticket);
    }
    catch(const AppError &ex) {
        this->handleAppError(ex);
        return;
    }
    this->ticket_table_model->addTicket(ticket);
}
