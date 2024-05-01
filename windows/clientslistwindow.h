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
    void init();

private slots:
    void onFindButtonClicked();
    void onSaveButtonClicked();

private:
    void refreshModel();
    QSharedPointer<ClientModel> client_model;
    Ui::ClientsListWindow *ui;

};

#endif // CLIENTSLISTWINDOW_H
