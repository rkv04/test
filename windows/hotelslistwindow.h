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
    void onBackButtonClicked();
    bool confirmDelete();

signals:
    void showEmployeeMainWindow();

private:
    void handleAppError(const AppError &ex);
    bool hasSelection();
    Ui::HotelsListWindow *ui;

    QSharedPointer<HotelCategoryListModel> category_model;
    QSharedPointer<HotelTableModel> hotel_table_model;
    QSharedPointer<CityListModel> city_list_model;
};

#endif // HOTELSLISTWINDOW_H
