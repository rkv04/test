#ifndef CLIENTMAINWINDOW_H
#define CLIENTMAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>

#include "myticketswindow.h"
#include "account.h"
#include "ticketpurchasewindow.h"

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
};

#endif // CLIENTMAINWINDOW_H
