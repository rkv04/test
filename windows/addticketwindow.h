#ifndef ADDTICKETWINDOW_H
#define ADDTICKETWINDOW_H

#include <QDialog>

namespace Ui {
class AddTicketWindow;
}

class AddTicketWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddTicketWindow(QWidget *parent = nullptr);
    ~AddTicketWindow();

private:
    Ui::AddTicketWindow *ui;
};

#endif // ADDTICKETWINDOW_H
