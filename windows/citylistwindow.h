#ifndef CITYLISTWINDOW_H
#define CITYLISTWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSharedPointer>

#include "addcitywindow.h"
#include "editcitywindow.h"
#include "citytablemodel.h"
#include "apperror.h"

namespace Ui {
class CityListWindow;
}

class CityListWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CityListWindow(QWidget *parent = nullptr);
    ~CityListWindow();

    void init();

private slots:
    void onAddButtonClicked();
    void onDeleteButtonClicked();
    void onEditButtonClicked();
    void onFindButtonClicked();
    void onBackButtonClicked();

signals:
    void showEmployeeMainWindow();

private:
    bool confirmDelete();
    bool tableHasSelection();
    void handleAppError(const AppError &ex);

    Ui::CityListWindow *ui;
    QSharedPointer<CityTableModel> city_table_model;
};

#endif // CITYLISTWINDOW_H
