#ifndef CITYLISTWINDOW_H
#define CITYLISTWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSharedPointer>

#include "addcitywindow.h"

namespace Ui {
class CityListWindow;
}

class CityListWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CityListWindow(QWidget *parent = nullptr);
    ~CityListWindow();

private slots:
    void onAddCityButtonClicked();

private:
    Ui::CityListWindow *ui;
    QSqlQueryModel *query_model;
    AddCityWindow *add_city_window;
};

#endif // CITYLISTWINDOW_H
