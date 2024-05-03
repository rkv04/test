#ifndef HOTELSLISTWINDOW_H
#define HOTELSLISTWINDOW_H

#include <QMainWindow>
#include "addhotelwindow.h"
#include "hotelmodel.h"

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
    void addHotel(const QSharedPointer<Hotel> &hotel);

private:
    Ui::HotelsListWindow *ui;
    AddHotelWindow *add_hotel_window;
    QSharedPointer<HotelModel> hotel_model;
};

#endif // HOTELSLISTWINDOW_H
