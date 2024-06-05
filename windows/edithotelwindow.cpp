#include "edithotelwindow.h"
#include "ui_edithotelwindow.h"

#include <QMessageBox>

#include "app.h"
#include "apperror.h"

EditHotelWindow::EditHotelWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditHotelWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(App::APPLICATION_NAME);
    connect(this->ui->saveButton, SIGNAL(clicked(bool)), this, SLOT(onSaveButtonClicked()));
    connect(this->ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
    this->city_list_model = QSharedPointer<CityListModel>(new CityListModel());
    this->category_model = QSharedPointer<HotelCategoryListModel>(new HotelCategoryListModel());
    this->ui->cityBox->setModel(city_list_model.get());
    this->ui->categoryBox->setModel(category_model.get());
}

EditHotelWindow::~EditHotelWindow()
{
    delete ui;
}

void EditHotelWindow::init() {
    QVector<QSharedPointer<City>> cities;
    App *app = App::getInstance();
    try {
        cities = app->getCityList();
    }
    catch(const AppError &ex) {
        QMessageBox::critical(this, App::APPLICATION_NAME, ex.what());
        if (ex.isFatal()) {
            exit(-1);
        }
        return;
    }
    this->city_list_model->setCityList(cities);
    this->city_list_model->addCityIfNotExists(this->hotel->city);
    this->ui->titleEdit->setText(hotel->title);
    this->ui->addressEdit->setText(hotel->address);
    int city_index = this->ui->cityBox->findText(hotel->city->title);
    this->ui->cityBox->setCurrentIndex(city_index);
    int category_index = this->ui->categoryBox->findData(hotel->category, HotelCategoryListModel::CategoryRole);
    this->ui->categoryBox->setCurrentIndex(category_index);
}

void EditHotelWindow::setHotel(const QSharedPointer<Hotel> &hotel) {
    this->hotel = hotel;
}

void EditHotelWindow::onSaveButtonClicked() {
    QString title = this->ui->titleEdit->text();
    QString address = this->ui->addressEdit->text();
    QSharedPointer<City> city = this->ui->cityBox->currentData(CityListModel::CityPtrRole).value<QSharedPointer<City>>();
    int category = this->ui->categoryBox->currentData(HotelCategoryListModel::CategoryRole).toInt();
    if (title.isEmpty() || address.isEmpty() || city == nullptr || category == -1) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Необходимо заполнить все поля формы");
        return;
    }
    this->hotel->title = title;
    this->hotel->address = address;
    this->hotel->category = category;
    this->hotel->city = city;
    EditHotelWindow::accept();
}
