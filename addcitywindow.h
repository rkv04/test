#ifndef ADDCITYWINDOW_H
#define ADDCITYWINDOW_H

#include <QDialog>

namespace Ui {
class AddCityWindow;
}

class AddCityWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddCityWindow(QWidget *parent = nullptr);
    ~AddCityWindow();

private:
    Ui::AddCityWindow *ui;
};

#endif // ADDCITYWINDOW_H
