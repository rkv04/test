#ifndef TICKETSLISTWINDOW_H
#define TICKETSLISTWINDOW_H

#include <QDialog>

namespace Ui {
class TicketsListWindow;
}

class TicketsListWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TicketsListWindow(QWidget *parent = nullptr);
    ~TicketsListWindow();

private:
    Ui::TicketsListWindow *ui;
};

#endif // TICKETSLISTWINDOW_H
