#ifndef HOTELSLISTWINDOW_H
#define HOTELSLISTWINDOW_H

#include <QMainWindow>
#include <QCompleter>

#include "addhotelwindow.h"
#include "edithotelwindow.h"
#include "hoteltablemodel.h"
#include "citylistmodel.h"
#include "hotelcategorylistmodel.h"
#include "city.h"
#include "apperror.h"

namespace Ui {
class HotelsListWindow;
}

class HotelsListWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HotelsListWindow(QWidget *parent = nullptr);
    ~HotelsListWindow();
    void init();

private slots:
    void onAddHotelButtonClicked();
    void onDeleteButtonClicked();
    void onEditButtonClicked();
    void onFindButtonClicked();
    void addHotel(const QSharedPointer<Hotel> &hotel);
    QSharedPointer<City> getCityByCityBoxIndex(const int index);
    bool confirmDelete();

private:
    void handleAppError(const AppError &ex);
    bool hasSelection();
    Ui::HotelsListWindow *ui;
    AddHotelWindow *add_hotel_window;
    EditHotelWindow *edit_hotel_window;

    QSharedPointer<HotelCategoryListModel> category_model;
    QSharedPointer<HotelTableModel> hotel_table_model;
    QSharedPointer<CityListModel> city_list_model;
};

#endif // HOTELSLISTWINDOW_H
