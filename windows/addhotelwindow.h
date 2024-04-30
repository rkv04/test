#ifndef ADDHOTELWINDOW_H
#define ADDHOTELWINDOW_H

#include <QDialog>
#include "citylistmodel.h"

namespace Ui {
class AddHotelWindow;
}

class AddHotelWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddHotelWindow(QWidget *parent = nullptr);
    ~AddHotelWindow();

private:
    Ui::AddHotelWindow *ui;
    QSharedPointer<CityListModel> city_list_model;
};

#endif // ADDHOTELWINDOW_H
