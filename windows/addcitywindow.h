#ifndef ADDCITYWINDOW_H
#define ADDCITYWINDOW_H

#include <QDialog>
#include "city.h"

namespace Ui {
class AddCityWindow;
}

class AddCityWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddCityWindow(QWidget *parent = nullptr);
    ~AddCityWindow();

private slots:
    void onAddButtonClicked();

signals:
    void cityCreated(const QSharedPointer<City> city);

private:
    Ui::AddCityWindow *ui;
};

#endif // ADDCITYWINDOW_H
