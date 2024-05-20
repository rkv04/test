#ifndef CLIENTTICKETSWINDOW_H
#define CLIENTTICKETSWINDOW_H

#include <QMainWindow>

#include "dealtablemodel.h"

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

private slots:
    void onBackButtonClicked();
    void onTicketClicked(const QModelIndex &index);

signals:
    void back();

private:
    Ui::ClientTicketsWindow *ui;

    void initModels();
    void initUi();
    QSharedPointer<DealTableModel> deal_table_model;
};

#endif // CLIENTTICKETSWINDOW_H
