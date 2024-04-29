#ifndef EDITTICKETWINDOW_H
#define EDITTICKETWINDOW_H

#include <QDialog>

namespace Ui {
class EditTicketWindow;
}

class EditTicketWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditTicketWindow(QWidget *parent = nullptr);
    ~EditTicketWindow();

private:
    Ui::EditTicketWindow *ui;
};

#endif // EDITTICKETWINDOW_H
