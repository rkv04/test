#ifndef USERSLISTWINDOW_H
#define USERSLISTWINDOW_H

#include <QDialog>

#include "clienttablemodel.h"
#include "employeetablemodel.h"

namespace Ui {
class UsersListWindow;
}

class UsersListWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UsersListWindow(QWidget *parent = nullptr);
    ~UsersListWindow();

    void init();

private slots:
    void onBackButtonClicked();
    void clientRadioButtonClicked();
    void employeeRadioButtonClicked();

signals:
    void back();

private:
    Ui::UsersListWindow *ui;

    void initModels();
    void initUi();

    QSharedPointer<ClientTableModel> client_table_model;
    QSharedPointer<EmployeeTableModel> employee_table_model;
};

#endif // USERSLISTWINDOW_H
