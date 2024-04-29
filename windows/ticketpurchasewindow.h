#ifndef TICKETPURCHASEWINDOW_H
#define TICKETPURCHASEWINDOW_H

#include <QDialog>

namespace Ui {
class TicketPurchaseWindow;
}

class TicketPurchaseWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TicketPurchaseWindow(QWidget *parent = nullptr);
    ~TicketPurchaseWindow();

private:
    Ui::TicketPurchaseWindow *ui;
};

#endif // TICKETPURCHASEWINDOW_H
