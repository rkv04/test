#ifndef EDITCITYWINDOW_H
#define EDITCITYWINDOW_H

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

private:
    Ui::EditCityWindow *ui;
};

#endif // EDITCITYWINDOW_H
