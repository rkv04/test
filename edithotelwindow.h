#ifndef EDITHOTELWINDOW_H
#define EDITHOTELWINDOW_H

#include <QDialog>

namespace Ui {
class EditHotelWindow;
}

class EditHotelWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditHotelWindow(QWidget *parent = nullptr);
    ~EditHotelWindow();

private:
    Ui::EditHotelWindow *ui;
};

#endif // EDITHOTELWINDOW_H
