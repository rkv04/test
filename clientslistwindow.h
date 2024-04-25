#ifndef CLIENTSLISTWINDOW_H
#define CLIENTSLISTWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>

#include "clientmodel.h"

namespace Ui {
class ClientsListWindow;
}

class ClientsListWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientsListWindow(QWidget *parent = nullptr);
    ~ClientsListWindow();

private slots:
    void onFindButtonClicked();
    void onSaveButtonClicked();

private:
    void init();
    void refreshModel();
    ClientModel *client_model;
    Ui::ClientsListWindow *ui;

};

#endif // CLIENTSLISTWINDOW_H
