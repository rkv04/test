#include "clientticketswindow.h"
#include "ui_clientticketswindow.h"

#include <QMessageBox>

#include "app.h"
#include "deal.h"
#include "apperror.h"
#include "context.h"

ClientTicketsWindow::ClientTicketsWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientTicketsWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(App::APPLICATION_NAME);
    connect(this->ui->backButton, SIGNAL(clicked(bool)), this, SLOT(onBackButtonClicked()));
    connect(this->ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(onTicketClicked(QModelIndex)));
    this->deal_table_model = QSharedPointer<DealTableModel>(new DealTableModel());
    this->ui->tableView->setModel(this->deal_table_model.get());
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->ui->tableView->horizontalHeader()->stretchLastSection();
}

ClientTicketsWindow::~ClientTicketsWindow()
{
    delete ui;
}

void ClientTicketsWindow::init() {
    this->initModels();
    this->initUi();
}

void ClientTicketsWindow::initUi() {
    this->ui->tableView->resizeColumnsToContents();
}

void ClientTicketsWindow::initModels() {
    QVector<QSharedPointer<Deal>> deals;
    auto client = Context::getContext();
    App *app = App::getInstance();
    try {
        deals = app->getDealListByClient(client);
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }
    this->deal_table_model->setDealsList(deals);
}

void ClientTicketsWindow::onBackButtonClicked() {
    emit back();
    this->close();
}

void ClientTicketsWindow::onTicketClicked(const QModelIndex &index) {
    auto deal = this->deal_table_model->getDealByIndexRow(index.row());
    this->ui->durationEdit->setText(QString::number(deal->ticket->duration));
    this->ui->travelTimeEdit->setText(deal->ticket->travel_time);
    this->ui->discountEdit->setText(QString::number(deal->discount) + "%");
    this->ui->purchaseDate->setText(deal->date.toString("dd.MM.yyyy"));
    this->ui->priceEdit->setText(QString::number(deal->deal_sum / 100.0, 'f', 2) + " руб.");
}
