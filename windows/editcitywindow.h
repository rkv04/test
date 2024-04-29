#ifndef EDITCITYWINDOW_H
#define EDITCITYWINDOW_H

#include "city.h"

#include <QDialog>

namespace Ui {
class EditCityWindow;
}

class EditCityWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditCityWindow(QWidget *parent = nullptr);
    ~EditCityWindow();
    void setCity(const QSharedPointer<City> city);

private slots:
    void onSaveButtonClicked();

private:
    Ui::EditCityWindow *ui;
    QSharedPointer<City> city;
};

#endif // EDITCITYWINDOW_H
