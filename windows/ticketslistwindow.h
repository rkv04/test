#ifndef TICKETSLISTWINDOW_H
#define TICKETSLISTWINDOW_H

#include <QDialog>

#include "tickettablemodel.h"
#include "apperror.h"
#include "addticketwindow.h"

namespace Ui {
class TicketsListWindow;
}

class TicketsListWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TicketsListWindow(QWidget *parent = nullptr);
    ~TicketsListWindow();

    void init();

private slots:
    void onAddTicketButtonClicked();

private:
    Ui::TicketsListWindow *ui;
    AddTicketWindow *add_ticket_window;

    void handleAppError(const AppError &ex);
    QSharedPointer<TicketTableModel> ticket_table_model;
};

#endif // TICKETSLISTWINDOW_H
