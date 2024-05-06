#ifndef EDITHOTELWINDOW_H
#define EDITHOTELWINDOW_H

#include <QDialog>
#include "hotel.h"
#include "citylistmodel.h"
#include "hotelcategorylistmodel.h"

namespace Ui {
class EditHotelWindow;
}

class EditHotelWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditHotelWindow(QWidget *parent = nullptr);
    ~EditHotelWindow();

    void init();
    void setHotel(const QSharedPointer<Hotel> &hotel);

private slots:
    void onSaveButtonClicked();

private:
    Ui::EditHotelWindow *ui;

    QSharedPointer<CityListModel> city_list_model;
    QSharedPointer<HotelCategoryListModel> category_model;
    QSharedPointer<Hotel> hotel;
};

#endif // EDITHOTELWINDOW_H
