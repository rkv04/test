#ifndef ADDHOTELWINDOW_H
#define ADDHOTELWINDOW_H

#include <QDialog>
#include "citylistmodel.h"
#include "hotelcategorylistmodel.h"
#include "hotel.h"

namespace Ui {
class AddHotelWindow;
}

class AddHotelWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddHotelWindow(QWidget *parent = nullptr);
    ~AddHotelWindow();
    void init();

signals:
    void hotelCreated(const QSharedPointer<Hotel> &hotel);

private slots:
    void onAddButtonClicked();

private:
    Ui::AddHotelWindow *ui;
    QSharedPointer<CityListModel> city_list_model;
    QSharedPointer<HotelCategoryListModel> category_model;
};

#endif // ADDHOTELWINDOW_H
