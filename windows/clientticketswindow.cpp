#include "clientticketswindow.h"
#include "ui_clientticketswindow.h"

#include <QMessageBox>

#include "app.h"
#include "apperror.h"

ClientTicketsWindow::ClientTicketsWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientTicketsWindow)
{
    ui->setupUi(this);
}

ClientTicketsWindow::~ClientTicketsWindow()
{
    delete ui;
}

void ClientTicketsWindow::init() {
    this->initModels();
    this->initUi();
}

void ClientTicketsWindow::initModels() {
    QVector<QSharedPointer<Ticket>> tickets;
    App *app = App::getInstance();
    try {
        tickets = app->getCurrentClientTicketList();
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, "Tour operator", ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }
    this->ticket_table_model = QSharedPointer<TicketTableModel>(new TicketTableModel());
    this->ticket_table_model->setTicketList(tickets);
}

void ClientTicketsWindow::initUi() {
    this->ui->tableView->setModel(this->ticket_table_model.get());
    this->ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);
    this->ui->tableView->resizeColumnsToContents();
    this->ui->tableView->verticalHeader()->stretchLastSection();
}
