#ifndef CLIENTSLISTWINDOW_H
#define CLIENTSLISTWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>

#include "sqlquerymodel.h"

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
    QSqlQueryModel *query_model;
    Ui::ClientsListWindow *ui;

};

#endif // CLIENTSLISTWINDOW_H
