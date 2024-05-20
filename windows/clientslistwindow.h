#ifndef CLIENTSLISTWINDOW_H
#define CLIENTSLISTWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>

#include "apperror.h"
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
    void onResetFiltersButtonClicked();

private:
    Ui::ClientsListWindow *ui;

    void initUi();
    void initModels();
    void handleAppError(const AppError &ex);
    QMap<QString, QString> createFilter();
    QSharedPointer<ClientTableModel> client_model;

};

#endif // CLIENTSLISTWINDOW_H
