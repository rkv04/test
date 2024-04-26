#include "citylistwindow.h"
#include "ui_citylistwindow.h"

#include <QMessageBox>

#include "addcitywindow.h"
#include "citymodel.h"
#include "app.h"
#include "apperror.h"

CityListWindow::CityListWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CityListWindow)
{
    ui->setupUi(this);

    App *app = App::getInstance();
    QVector<QSharedPointer<City>> city_list;
    try {
        city_list = app->getCityList();
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, "Tour operator", ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }

    this->city_model = QSharedPointer<CityModel>(new CityModel());
    this->city_model->setCityList(city_list);
    this->ui->tableView->setModel(city_model.get());
    this->ui->tableView->horizontalHeader()->setStretchLastSection(true);
    this->ui->tableView->setWordWrap(true);

    this->ui->tableView->verticalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


    connect(this->ui->addCityButton, SIGNAL(clicked(bool)), this, SLOT(onAddCityButtonClicked()));
}

CityListWindow::~CityListWindow()
{
    delete ui;
}

void CityListWindow::onAddCityButtonClicked() {
    this->add_city_window = new AddCityWindow();
    this->add_city_window->setModal(true);
    this->add_city_window->exec();
}
