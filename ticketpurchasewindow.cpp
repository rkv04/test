#include "ticketpurchasewindow.h"
#include "ui_ticketpurchasewindow.h"

TicketPurchaseWindow::TicketPurchaseWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TicketPurchaseWindow)
{
    ui->setupUi(this);
}

TicketPurchaseWindow::~TicketPurchaseWindow()
{
    delete ui;
}
