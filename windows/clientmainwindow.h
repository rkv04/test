#ifndef CLIENTMAINWINDOW_H
#define CLIENTMAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>

#include "account.h"
#include "ticketpurchasewindow.h"
#include "clientticketswindow.h"

namespace Ui {
class ClientMainWindow;
}

class ClientMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientMainWindow(QWidget *parent = nullptr);
    ~ClientMainWindow();

private slots:
    void onAccountButtonClicked();
    void onOffersButtonClicked();
    void onTicketsButtonClicked();

signals:
    void logout();

private:
    Ui::ClientMainWindow *ui;

    QSharedPointer<Account> account_window;
    QSharedPointer<TicketPurchaseWindow> ticket_purchase_window;
    QSharedPointer<ClientTicketsWindow> client_ticket_window;

};

#endif // CLIENTMAINWINDOW_H
