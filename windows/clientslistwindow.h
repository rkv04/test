#ifndef CLIENTSLISTWINDOW_H
#define CLIENTSLISTWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>

#include "clienttablemodel.h"

namespace Ui {
class ClientsListWindow;
}

class ClientsListWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientsListWindow(QWidget *parent = nullptr);
    ~ClientsListWindow();
    void init();

signals:
    void showEmployeeMainWindow();

private slots:
    void onFindButtonClicked();
    void onSaveButtonClicked();
    void onBackButtonClicked();

private:
    void refreshModel();
    QSharedPointer<ClientTableModel> client_model;
    Ui::ClientsListWindow *ui;

};

#endif // CLIENTSLISTWINDOW_H
