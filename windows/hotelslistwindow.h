#ifndef HOTELSLISTWINDOW_H
#define HOTELSLISTWINDOW_H

#include <QMainWindow>
#include "addhotelwindow.h"
#include "hoteltablemodel.h"
#include "citylistmodel.h"
#include "city.h"

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
    void onFindButtonClicked();
    void onDeleteButtonClicked();
    void addHotel(const QSharedPointer<Hotel> &hotel);
    QSharedPointer<City> getCityByCityBoxIndex(const int index);
    bool confirmDelete();

private:
    Ui::HotelsListWindow *ui;
    AddHotelWindow *add_hotel_window;
    QSharedPointer<HotelTableModel> hotel_table_model;
    QSharedPointer<CityListModel> city_list_model;
};

#endif // HOTELSLISTWINDOW_H
