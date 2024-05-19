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
    connect(this->ui->backButton, SIGNAL(clicked(bool)), this, SLOT(onBackButtonClicked()));
    this->deal_table_model = QSharedPointer<DealTableModel>(new DealTableModel());
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
    QVector<QSharedPointer<Deal>> deals;
    auto client = Context::getContext();
    App *app = App::getInstance();
    try {
        deals = app->getDealListByClient(client);
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, "Tour operator", ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }
    this->deal_table_model->setDealsList(deals);
}

void ClientTicketsWindow::initUi() {
    this->ui->tableView->setModel(this->deal_table_model.get());
    this->ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);
    this->ui->tableView->resizeColumnsToContents();
    this->ui->tableView->verticalHeader()->stretchLastSection();
}

void ClientTicketsWindow::onBackButtonClicked() {
    emit back();
    this->close();
}
