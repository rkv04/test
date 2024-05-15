#ifndef CLIENTTICKETSWINDOW_H
#define CLIENTTICKETSWINDOW_H

#include <QMainWindow>

#include "tickettablemodel.h"

namespace Ui {
class ClientTicketsWindow;
}

class ClientTicketsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientTicketsWindow(QWidget *parent = nullptr);
    ~ClientTicketsWindow();

    void init();

private:
    Ui::ClientTicketsWindow *ui;

    void initModels();
    void initUi();
    QSharedPointer<TicketTableModel> ticket_table_model;
};

#endif // CLIENTTICKETSWINDOW_H
