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
    connect(this->ui->saveButton, SIGNAL(clicked(bool)), this, SLOT(onSaveButtonClicked()));
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
    this->city_list_model = QSharedPointer<CityListModel>(new CityListModel());
    this->city_list_model->setCityList(cities);
    this->ui->cityBox->setModel(city_list_model.get());

    this->category_model = QSharedPointer<HotelCategoryListModel>(new HotelCategoryListModel());
    this->ui->categoryBox->setModel(category_model.get());
}

void EditHotelWindow::setHotel(const QSharedPointer<Hotel> &hotel) {
    this->hotel = hotel;
    this->ui->titleEdit->setText(hotel->title);
    this->ui->addressEdit->setText(hotel->address);
    int city_index = this->ui->cityBox->findText(hotel->city->title);
    this->ui->cityBox->setCurrentIndex(city_index);
    int category_index = this->ui->categoryBox->findData(hotel->category, Qt::UserRole);
    this->ui->categoryBox->setCurrentIndex(category_index);
}

void EditHotelWindow::onSaveButtonClicked() {
    int city_index = this->ui->cityBox->currentIndex();
    QString title = this->ui->titleEdit->text();
    QString address = this->ui->addressEdit->text();
    if (title.isEmpty() || address.isEmpty() || city_index == 0) {
        QMessageBox::warning(this, App::APPLICATION_NAME, "Необходимо заполнить все поля формы");
        return;
    }
    this->hotel->title = title;
    this->hotel->address = address;
    int category_index = this->ui->categoryBox->currentIndex();
    this->hotel->category = this->category_model->getCategoryByIndex(category_index);
    this->hotel->city = this->city_list_model->getCityByIndex(city_index - 1);
    EditHotelWindow::accept();
}
