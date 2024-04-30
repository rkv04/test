#ifndef HOTELSLISTWINDOW_H
#define HOTELSLISTWINDOW_H

#include <QMainWindow>
#include "addhotelwindow.h"

namespace Ui {
class HotelsListWindow;
}

class HotelsListWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HotelsListWindow(QWidget *parent = nullptr);
    ~HotelsListWindow();

private slots:
    void onAddHotelButtonClicked();

private:
    Ui::HotelsListWindow *ui;
    AddHotelWindow *add_hotel_window;
};

#endif // HOTELSLISTWINDOW_H
